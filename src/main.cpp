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

// --- Sensors
SoilMoistureSensor<PIN_SENSOR_GROUND_HUMIDITY> soilSensor;
UVSensor<PIN_SENSOR_UV> uvSensor;
BMESensor<ADDR_SENSOR_BME> bmeSensor;
LightSensor<ADDR_SENSOR_LIGHT> lightSensor;


constexpr size_t MEASUREMENT_COUNT = SensorUtil::accumulateSensorSizes(soilSensor, uvSensor, bmeSensor, lightSensor);


// -- Internals
TaskBuffer<10> buffer;
TaskManager tasks{buffer};

void setup()
{
  ENABLE_SERIAL(9600);

  lightSensor.begin();
  if(!bmeSensor.begin())
    LOG_LN("BME FAILED!");

  tasks.registerTask([](){ util::printSensorData(soilSensor); }, 1000);
  tasks.registerTask([](){ util::printSensorData(bmeSensor); }, 1000);
  tasks.registerTask([](){ util::printSensorData(uvSensor); }, 1000);
  tasks.registerTask([](){ util::printSensorData(lightSensor); }, 1000);
  
  LOG_LN("Hellokidoki, De weerman is wakker");
}

void loop()
{
  tasks.update();
}
