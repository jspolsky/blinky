#include <Arduino.h>
#include <ArduinoLowPower.h>

#include "matrix.h"
#include "util.h"
#include "button.h"
#include "irreceive.h"

void setup()
{
  Matrix::setup();
  Util::setup();
  Button::setup();
  Irreceive::setup();
}

void loop()
{
  Button::loop();
  Irreceive::loop();

  if (Irreceive::can_sleep())
  {
    Util::setColorRGB(0, 0, 0);
    Button::sleep();
    Irreceive::sleep();
    LowPower.deepSleep();
  }
}
