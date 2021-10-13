#include <Arduino.h>
#include <ArduinoLowPower.h>

#define DECODE_NEC
#include <IRremote.h>

#include "matrix.h"
#include "util.h"
#include "button.h"

volatile uint8_t irActivity = 0; // changes to 1 when the interrupt fires

IRrecv irrecv(A1);

void irActivityISR()
{
  // woken up by ir
  irActivity = 1;
}

void setup()
{
  Serial.begin(9600);

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);

  Matrix::setup();
  Util::setup();
  Button::setup();

  LowPower.attachInterruptWakeup(A1, irActivityISR, FALLING);

  LowPower.sleep(20000);
}

void loop()
{

  Button::loop();

  // TESTING IR
  if (irActivity)
  {
    irrecv.enableIRIn(); // Start the receiver
    irActivity = false;
  }

  if (irrecv.decode())
  {
    if (irrecv.decodedIRData.address == 0xCFFE)
    {
      // it's for us!
      Util::setColorHSV(irrecv.decodedIRData.command);
    }

    IrReceiver.resume();
  }
}
