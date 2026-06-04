#include <Arduino.h>
#include <taskmanager.h>

#include "constants.h"

#include <Sensor.h>
#include <BMESensor.h>

#include <SoilMoistureSensor.h>
#include <UVSensor.h>
#include <BMESensor.h>
#include <LightSensor.h>

SoilMoistureSensor<PIN_SENSOR_GROUND_HUMIDITY> soilSensor;
UVSensor<PIN_SENSOR_UV> uvSensor;
BMESensor<ADDR_SENSOR_BME> bmeSensor;
LightSensor<ADDR_SENSOR_LIGHT> lightSensor;

template <typename TImpl>
void printSensorData(SensorBase<TImpl>& sensor) {
  DataPoint dataPoints[sensor.size()];
  // Serial.println(sensor.size());
  sensor.fillData(dataPoints);
  for (auto i = 0U; i < sensor.size(); i++)
  {
    Serial.print(dataPoints[i].m_name);
    Serial.print(" : ");
    Serial.println(dataPoints[i].m_value);
  }
  Serial.println("---------");
}

// Fwd declarations
void blink();

// SensorBase base;

void flashTwice()
{
  Serial.print("Flashy! ");
  Serial.println(millis());
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
  }
}

void printSoil()
{
  printSensorData(soilSensor);
}

void printUV() {
  printSensorData(uvSensor);
}

void printHello()
{
  Serial.print("HELLOOO ");
  Serial.println(millis());
}

TaskBuffer<10> buffer;
TaskManager tasks{buffer};

void setup()
{
  Serial.begin(9600);
  lightSensor.begin();
  if(!bmeSensor.begin())
    Serial.println("BME FAILED!");

  //tasks.registerTask(&flashTwice, 10000);
  tasks.registerTask([](){ printSensorData(soilSensor); }, 1000);
  tasks.registerTask([](){ printSensorData(bmeSensor); }, 1000);
  tasks.registerTask([](){ printSensorData(uvSensor); }, 1000);
  tasks.registerTask([](){ printSensorData(lightSensor); }, 1000);
  tasks.registerTask([](){ Serial.println("\n\n\n"); }, 1000);

  // tasks.registerTask(&printHello, 1000);

  pinMode(LED_BUILTIN, OUTPUT);

  
  Serial.println("Hellokidoki");
}

void loop()
{

  tasks.update();
}

void blink()
{
  digitalWrite(LED_BUILTIN, HIGH);

  delay(300);

  for (int i = 0; i < 20; i++)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }
  digitalWrite(LED_BUILTIN, LOW);
}