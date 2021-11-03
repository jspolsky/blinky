#include <Arduino.h>
#include <ArduinoLowPower.h>

#include "matrix.h"
#include "util.h"
#include "button.h"
#include "ir.h"

void LongPressStart();
void LongPressEnd();
void ShortPress();

void setup()
{
  Matrix::setup();
  Matrix::displayAnimation(0);
  Util::setup();
  Button::setup(LongPressStart, LongPressEnd, ShortPress);
  IR::setup();
}

void loop()
{
  Button::loop();
  IR::loop();

  if (Button::can_sleep() && IR::can_sleep())
  {
    Button::sleep();
    IR::sleep();
    LowPower.sleep();
  }
}

/**************************
 *  CALLBACKS FROM BUTTON *
 **************************/

void LongPressStart()
{
  IR::start();
}

void LongPressEnd()
{
  IR::end();
}

void ShortPress()
{
  Util::setColorRGB(0, 0, 0xFF);
  Matrix::displayAnimation(0);
}
