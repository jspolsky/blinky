#include <Arduino.h>
#include <ArduinoLowPower.h>

#include "matrix.h"
#include "util.h"
#include "button.h"
#include "ir.h"
#include "inventory.h"
#include "powersave.h"

void LongPressStart();
void LongPressEnd();
void ShortPress();

void setup()
{
  Inventory::setup();
  Matrix::setup();
  Matrix::displayAnimation(Inventory::getCurrentAnimation());
  Util::setup();
  Button::setup(LongPressStart, LongPressEnd, ShortPress);
  IR::setup();
  PowerSave::setup();
}

void loop()
{
  PowerSave::loop();
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
  PowerSave::reset();
  IR::start();
}

void LongPressEnd()
{
  PowerSave::reset();
  IR::end();
}

void ShortPress()
{
  PowerSave::reset();
  Matrix::displayAnimation(Inventory::nextAnimation());
}
