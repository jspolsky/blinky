#include <Arduino.h>
#include <ArduinoLowPower.h>

#include "matrix.h"
#include "util.h"
#include "button.h"
#include "irreceive.h"

void setup()
{
  Matrix::setup();
  Matrix::displayAnimation(0);
  Util::setup();
  Button::setup();
  //  Irreceive::setup();
}

void loop()
{
  Button::loop();
  //  Irreceive::loop();

  if (Irreceive::can_sleep() && Button::can_sleep())
  {
    Button::sleep();
    //    Irreceive::sleep();
    LowPower.sleep();
  }
}
