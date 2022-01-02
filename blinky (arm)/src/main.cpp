#include <Arduino.h>
#include <ArduinoLowPower.h>
#include <SPI.h>

#include "matrix.h"
#include "util.h"
#include "button.h"
#include "ir.h"
#include "inventory.h"
#include "powersave.h"

void setup()
{
  Matrix::setup();
  Inventory::setup();
  Matrix::displayAnimation(Inventory::getCurrentAnimation());
  Util::setup();

#ifdef BLINKY
  IR::setup();
  PowerSave::setup();
  Button::setup();
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
  if (!PowerSave::loop())
  {
    Button::loop();
  }

  LowPower.sleep();
#endif

#ifdef PREVIEW

  static bool waiting_for_cframes = false;
  static bool waiting_for_animation = false;
  static uint8_t cframes = 0;

#define ANIMATION_DATA_BUFFER_SIZE (8 * 9 * 16 / 2) + 2 /* 8*9*16 = max space for animation; 2 for delay */
  static uint8_t animation_data[ANIMATION_DATA_BUFFER_SIZE];
  static size_t animation_data_index = 0;
  static size_t cbWanted = 0;

  if (Serial.available() > 0)
  {

    if (waiting_for_cframes)
    {
      cframes = Serial.read();
      cbWanted = 2 + (cframes * 9 * 16 / 2);
      animation_data_index = 0;
      waiting_for_cframes = false;
      waiting_for_animation = true;
      Util::setColorRGB(255, 0, 0);
    }
    else if (waiting_for_animation)
    {
      size_t cbRead = Serial.readBytes((char *)(animation_data + animation_data_index),
                                       cbWanted - animation_data_index);
      animation_data_index += cbRead;
      if (animation_data_index >= cbWanted)
      {
        waiting_for_animation = false;
        uint16_t delay = animation_data[0] * 16 + animation_data[1];
        Matrix::displayAnimation(cframes, delay, animation_data + 2);
        Util::setColorRGB(0, 0, 255);
      }
    }
    else
    {
      int b = Serial.read();

      if (b == '?')
      {
        // for terminal debugging by a human
        Serial.println("Blinky Preview Ready");
      }
      else if (b == '!')
      {
        waiting_for_cframes = true;
      }
    }
  }

#endif
}
