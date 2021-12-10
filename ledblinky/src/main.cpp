#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:
  pinMode(A0, OUTPUT);
}

void loop()
{

  digitalWrite(A0, HIGH);
  delay(2000);
  digitalWrite(A0, LOW);
  delay(2000);
}