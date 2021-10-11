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

void setup()
{
  Serial.begin(9600);
  Serial.println("ISSI swirl test");

  pinMode(A0, INPUT_PULLUP);

  if (!ledmatrix.begin())
  {
    Serial.println("IS31 not found");
    while (1)
      ;
  }
  Serial.println("IS31 found!");

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
  // set the first pixel #0 to orange
  pixels.setPixelColor(0, pixels.Color(0x65, 0x43, 0x21));
  // and write the data
  pixels.show();

  //  LowPower.sleep(5000);
}

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void loop()
{
  // animate over all the pixels, and set the brightness from the sweep table
  // static uint8_t frame = 0;
  // ledmatrix.displayFrame(frame);
  // delay(100);
  // frame = (frame + 1) % 8;

  static int lastButtonState = LOW;
  static int buttonState = LOW;

  int reading = digitalRead(A0);
  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading != buttonState)
    {
      buttonState = reading;
      if (buttonState == LOW)
      {
        zToggle = !zToggle;
        pixels.setPixelColor(0, zToggle ? pixels.Color(0, 0xFF, 0)
                                        : pixels.Color(0xff, 0, 0));
        pixels.show();
      }
    }
  }

  lastButtonState = reading;
}
