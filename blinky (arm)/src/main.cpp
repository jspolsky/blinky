#include <Arduino.h>
#include <ArduinoLowPower.h>
#include <SPI.h>

#include "matrix.h"
#include "util.h"
#include "button.h"
#include "ir.h"
#include "inventory.h"
#include "powersave.h"
#include "preview.h"

void setup()
{
  Util::setup();

  Matrix::setup();
  Inventory::setup();
  Matrix::displayAnimation(Inventory::getCurrentAnimation());

#ifdef PREVIEW
  Preview::setup();
#endif

#ifdef BLINKY
  IR2::setup();
  PowerSave::setup();
  Button::setup();
#endif
}

void loop()
{

#ifdef BLINKY
  if (!PowerSave::loop())
  {
    Button::loop();
  }

  LowPower.sleep();
#endif

#ifdef PREVIEW
  Preview::loop();
#endif
}
