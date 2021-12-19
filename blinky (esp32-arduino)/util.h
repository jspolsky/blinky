#pragma once
#include <Arduino.h>

namespace Util 
{
  void setup();
  void setColorRGB(uint8_t red, uint8_t green, uint8_t blue);
  void setColorHSV(uint8_t hue, uint8_t saturation, uint8_t brightness);
}
