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

#ifdef BLINKY
  Button::setup(LongPressStart, LongPressEnd, ShortPress);
  IR::setup();
  PowerSave::setup();
#endif

#ifdef PREVIEW
  Serial.begin(9600);
  while (!Serial)
    ;
#endif
}

void loop()
{

#ifdef BLINKY
  PowerSave::loop();
  Button::loop();
  IR::loop();

  if (Button::can_sleep() && IR::can_sleep())
  {
    Button::sleep();
    IR::sleep();
    LowPower.sleep();
  }
#endif

#ifdef PREVIEW

  if (Serial.available() > 0)
  {
    int b = Serial.read();

    if (b == '?')
    {
      Serial.println("Blinky Preview Ready");
    }
  }

#endif
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
