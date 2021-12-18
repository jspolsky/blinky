#include <Arduino.h>

#include "button.h"
#include "pins.h"
#include "util.h"

namespace Button
{
  static CALLBACK *fnLongPressStart;
  static CALLBACK *fnLongPressEnd;
  static CALLBACK *fnShortPress;

  bool fButtonDown = false;
  bool fInLongPress = false;
  unsigned long tmDown = 0L;

  const unsigned long SHORT_CLICK_MS = 10L;  // how long button must be pressed to read a short click
  const unsigned long LONG_CLICK_MS = 1000L; // how long button must be pressed to read a long click

  void setup(CALLBACK *_fnLongPressStart, CALLBACK *_fnLongPressEnd, CALLBACK *_fnShortPress)
  {
    fnLongPressStart = _fnLongPressStart;
    fnLongPressEnd = _fnLongPressEnd;
    fnShortPress = _fnShortPress;

    pinMode(PIN_BUTTON, INPUT_PULLUP);
  }

  void loop()
  {

    if (fButtonDown) {

      if (HIGH == digitalRead(PIN_BUTTON))
      {
        // button released
        fButtonDown = false;

        if (fInLongPress)
        {
          fInLongPress = false;
          fnLongPressEnd();
          Util::setColorRGB(0,0,0);
        }
        else if (tmDown + SHORT_CLICK_MS < millis()) {
          // was down long enough to count as a short 
          // click 

          fnShortPress();
          Util::setColorRGB(0,255,0);

        }
      }
      else 
      {
        if (tmDown + LONG_CLICK_MS < millis()) {
          // was down long enough to count as long click

          fInLongPress = true;
          fnLongPressStart();
          Util::setColorRGB(0,0,255);

        }
      }

    } else {

      if (LOW == digitalRead(PIN_BUTTON))
      {
        // button pressed
        fButtonDown = true;
        tmDown = millis();
        Util::setColorRGB(255,0,0);
      }

    }

  }
}
