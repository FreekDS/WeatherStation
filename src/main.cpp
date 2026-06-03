#include <Arduino.h>
#include <taskmanager.h>

// Fwd declarations
void blink();

void flashTwice() {
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
  }
}

void printHello() {
  Serial.print("HELLOOO ");
  Serial.println(millis());
}


TaskBuffer<10> buffer;
TaskManager tasks{buffer};


void setup()
{
  //tasks.registerTask(&blink, 5000);
  tasks.registerTask(&printHello, 1000);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("Hellokidoki");
}

void loop()
{

  tasks.update();
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