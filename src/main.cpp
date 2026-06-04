#include <Arduino.h>
#include <taskmanager.h>

#include "constants.h"

#include <Sensor.h>
#include <BMESensor.h>
#include <SoilMoistureSensor.h>

SoilMoistureSensor<PIN_SENSOR_GROUND_HUMIDITY> soilSensor;

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
  DataPoint dataPoints[soilSensor.size()];
  soilSensor.fillData(dataPoints);
  for (auto i = 0U; i < soilSensor.size(); i++)
  {
    Serial.print(dataPoints[i].m_name);
    Serial.print(" : ");
    Serial.println(dataPoints[i].m_value);
  }
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
  tasks.registerTask(&flashTwice, 10000);
  tasks.registerTask(&printSoil, 1000);
  // tasks.registerTask(&printHello, 1000);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
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