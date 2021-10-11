#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include <ArduinoLowPower.h>
#include <Adafruit_NeoPixel.h>

Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();
Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL);
bool zToggle = 0;

// The lookup table to make the brightness changes be more visible
const uint8_t gamma_scale[] = {0, 1, 2, 4,
                               6, 10, 13, 18,
                               22, 28, 33, 39,
                               46, 53, 61, 69};

#define ____ 0
#include "../../hexels/bouncyheart.h"

volatile uint8_t buttonPressed = 0; // changes to 1 when the interrupt fires

// interrupt service routine for when a button (A0) is pressed
volatile unsigned long button_time = 0;
volatile unsigned long last_button_time = 0;
const unsigned long debounceDelay = 50;

void buttonPressISR()
{
  unsigned long button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    buttonPressed = 1;
    last_button_time = button_time;
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(A0, INPUT_PULLUP);

  if (!ledmatrix.begin())
  {
    Serial.println("IS31 not found");
    while (1)
      ;
  }

  // Write all 8 frames

  const uint8_t *pnext = a;

  for (uint8_t frame = 0; frame < 8; frame++)
  {
    ledmatrix.setFrame(frame);
    for (int x = 0; x < 16; x++)
      for (int y = 0; y < 9; y++)
        ledmatrix.drawPixel(15 - x, y, gamma_scale[(*pnext++) >> 4]);
  }

  ledmatrix.autoPlay(125);

  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(0x65, 0x43, 0x21));
  pixels.show();

  LowPower.attachInterruptWakeup(A0, buttonPressISR, FALLING);
  LowPower.sleep(10000);
}

void loop()
{
  // Toggle the color

  if (buttonPressed)
  {
    zToggle = !zToggle;
    pixels.setPixelColor(0, zToggle ? pixels.Color(0, 0xAF, 0)
                                    : pixels.Color(0xAF, 0, 0xAF));
    pixels.show();
    buttonPressed = false;
  }
}
