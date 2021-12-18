
#include <Adafruit_NeoPixel.h>

#include "util.h"
#include "pins.h"

Adafruit_NeoPixel strip(1, PIN_ONBOARD_NEOPIXEL, NEO_GRB + NEO_KHZ800);

namespace Util {

  void setup() 
  {

    strip.begin();
    strip.show();
    strip.setBrightness(50);

  }

  void setColorRGB(uint8_t red, uint8_t green, uint8_t blue)
  {
    strip.setPixelColor(0, strip.Color(red, green, blue));
    strip.show();

  }

  void setColorHSV(uint8_t hue, uint8_t saturation, uint8_t brightness)
  {
    strip.setPixelColor(0, strip.ColorHSV(hue << 8, saturation, brightness));
    strip.show();
  }

}
