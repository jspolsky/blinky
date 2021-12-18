// blinky for the ESP32C3

#include "util.h"
#include "button.h"

void setup()
{

  Util::setup();
  Button::setup(LongPressStart, LongPressEnd, ShortPress);

  // well this is a start
}

void loop()
{
  Button::loop();
}

void LongPressStart()
{
}

void LongPressEnd()
{
}

void ShortPress()
{
}