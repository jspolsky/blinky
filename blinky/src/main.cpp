#include <Arduino.h>
#include <ArduinoLowPower.h>

#include "matrix.h"
#include "util.h"
#include "button.h"
#include "irreceive.h"

void LongPressStart();
void LongPressEnd();
void ShortPress();

void setup()
{
  Matrix::setup();
  Matrix::displayAnimation(0);
  Util::setup();
  Button::setup(LongPressStart, LongPressEnd, ShortPress);
  Irreceive::setup();
}

void loop()
{
  Button::loop();
  Irreceive::loop();

  if (Button::can_sleep())
  {
    Button::sleep();
    LowPower.sleep();
  }
}

/**************************
 *  CALLBACKS FROM BUTTON *
 **************************/

void LongPressStart()
{
  Util::setColorRGB(0x65, 0x43, 0x21);
  Matrix::displayAnimation(1);
}

void LongPressEnd()
{
  Util::setColorRGB(0, 0, 0);
  Matrix::displayAnimation(2);
}

void ShortPress()
{
  Util::setColorRGB(0, 0, 0xFF);
  Matrix::displayAnimation(0);
}
