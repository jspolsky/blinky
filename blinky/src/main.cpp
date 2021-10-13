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

  LowPower.sleep(20000);
}

void loop()
{
  Button::loop();
  Irreceive::loop();
}
