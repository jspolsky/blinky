// blinky for the ESP32C3

#include "util.h"

void setup()
{

  Util::setup();

  // well this is a start
}

void loop()
{
  static uint8_t hue = 0;
  Util::setColorHSV(hue, 255, 255);
  hue++;
  delay(25);
}
