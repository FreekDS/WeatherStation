#include <Arduino.h>
#include "constants.h"

#include <taskmanager.h>
#include <logging.h>
#include <util.h>

#include <BMESensor.h>
#include <SoilMoistureSensor.h>
#include <UVSensor.h>
#include <BMESensor.h>
#include <LightSensor.h>

#include <JsonStreamer.h>
#include <MeasurementBuffer.h>

// --- Sensors
SoilMoistureSensor<PIN_SENSOR_GROUND_HUMIDITY> soilSensor;
UVSensor<PIN_SENSOR_UV> uvSensor;
BMESensor<ADDR_SENSOR_BME> bmeSensor;
LightSensor<ADDR_SENSOR_LIGHT> lightSensor;

// -- Measurement storage
constexpr size_t MEASUREMENT_COUNT = SensorUtil::accumulateSensorSizes(soilSensor, uvSensor, bmeSensor, lightSensor);
constexpr size_t MEASUREMENT_ITERATIONS = 10;
MeasurementBuffer<MEASUREMENT_COUNT * MEASUREMENT_ITERATIONS> measurementBuffer;

// -- Output serialization
constexpr size_t MAX_JSON_SIZE = 512;
//volatile char outputBuffer[MAX_JSON_SIZE];

// -- Internals
TaskBuffer<10> buffer;
TaskManager tasks{buffer};


void readSensors();
void logSerialData();
void sendBuffer();

void setup()
{
  ENABLE_SERIAL(9600);

  lightSensor.begin();
  if (!bmeSensor.begin())
    LOG_LN("BME FAILED!");

  tasks.registerTask([](){ LOG_LN("Heartbeat"); }, 1000);
  /*
  tasks.registerTask([](){ util::printSensorData(bmeSensor); }, 1000);
  tasks.registerTask([](){ util::printSensorData(uvSensor); }, 1000);
  tasks.registerTask([](){ util::printSensorData(lightSensor); }, 1000);
  */

  tasks.registerTask(&readSensors, 2000);
  //tasks.registerTask(&logSerialData, 8000);
  tasks.registerTask(&sendBuffer, 8000);

  LOG_LN("Hellokidoki, De weerman is wakker");
}

void loop()
{
  tasks.update();
}

void readSensors() {
  if(!measurementBuffer.readSensors(soilSensor, uvSensor, bmeSensor, lightSensor))
      LOG_LN("Measurement buffer overflow!");
}

void logSerialData()
{
  LOG("===LOG ");
  LOG(millis());
  LOG_LN("===");
  JsonStreamer::streamToSerial(measurementBuffer.begin(), measurementBuffer.size(), true);
  measurementBuffer.clear();
}


void sendBuffer()
{
  LOG("===LOG ");
  LOG(millis());
  LOG_LN("===");

  for(size_t i = 0; i < MEASUREMENT_ITERATIONS; i++)
  {
    char buffer[512];
    if(measurementBuffer.begin() + MEASUREMENT_COUNT * i >= measurementBuffer.end())
      break;
    JsonStreamer::streamToBuffer(measurementBuffer.begin() + MEASUREMENT_COUNT * i, MEASUREMENT_COUNT, buffer, 512);
    LOG_LN(buffer);
  }
  LOG_LN("");
  measurementBuffer.clear();
}
