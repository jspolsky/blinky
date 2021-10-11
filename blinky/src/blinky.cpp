#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include <Adafruit_SleepyDog.h>

// If you're using the full breakout...
Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
//Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();

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
  int sleepNow = Watchdog.sleep(); // TODO this comes on again quickly. gotta learn how this is supposed to work
}

void loop()
{
  // animate over all the pixels, and set the brightness from the sweep table
  // static uint8_t frame = 0;
  // ledmatrix.displayFrame(frame);
  // delay(100);
  // frame = (frame + 1) % 8;
}
