// blinky for the ESP32C3

#include <Adafruit_NeoPixel.h>
#include "pins.h"

Adafruit_NeoPixel strip(1, PIN_ONBOARD_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup()
{

  // well this is a start

  strip.begin();
  strip.show();
  strip.setBrightness(50);
}

void loop()
{

  static uint16_t hue = 0;
  strip.setPixelColor(0, Adafruit_NeoPixel::ColorHSV(hue));
  strip.show();
  hue += 65536 / 90;
  delay(100);
}
