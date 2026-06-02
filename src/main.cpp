#include <Arduino.h>
#include <taskmanager.h>

// Fwd declarations
void blink();

TaskManager tasks{100, &blink};


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  tasks.tick();
}

void blink() {
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