#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include <ArduinoLowPower.h>
#define DECODE_NEC
#include <IRremote.h>

#include "matrix.h"
#include "util.h"

bool zToggle = 0;

volatile uint8_t buttonPressed = 0; // changes to 1 when the interrupt fires
volatile uint8_t irActivity = 0;    // changes to 1 when the interrupt fires

// interrupt service routine for when a button (A0) is pressed
volatile unsigned long button_time = 0;
volatile unsigned long last_button_time = 0;
const unsigned long debounceDelay = 50;

IRrecv irrecv(A1);

void buttonPressISR()
{
  unsigned long button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    buttonPressed = 1;
    last_button_time = button_time;
  }
}

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

  LowPower.attachInterruptWakeup(A0, buttonPressISR, FALLING);
  LowPower.attachInterruptWakeup(A1, irActivityISR, FALLING);

  LowPower.sleep(20000);
}

void loop()
{
  // Toggle the color

  if (buttonPressed)
  {
    zToggle = !zToggle;
    if (zToggle)
      Util::setColorRGB(0, 0xAF, 0);
    else
      Util::setColorRGB(0xAF, 0, 0xAF);

    buttonPressed = false;
  }

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
