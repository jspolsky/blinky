#include <Arduino.h>
#include <ArduinoLowPower.h>
#include "util.h"
#include "button.h"
#include "pins.h"
#include "matrix.h"

namespace Button
{
    volatile bool fDown = false;
    volatile bool fUp = false;
    unsigned long tmDown = 0L;
    bool fInSwap = false;
    static CALLBACK *fnLongPressStart;
    static CALLBACK *fnLongPressEnd;
    static CALLBACK *fnShortPress;

    const unsigned long SHORT_CLICK_MS = 10L;  // how long button must be pressed to read a short click
    const unsigned long LONG_CLICK_MS = 1000L; // how long button must be pressed to read a long click

    void buttonISR()
    {
        int state = digitalRead(BUTTON_PIN);
        fDown = (state == LOW);
        fUp = (state == HIGH);
    }

    void setup(CALLBACK *_fnLongPressStart, CALLBACK *_fnLongPressEnd, CALLBACK *_fnShortPress)
    {
        fnLongPressStart = _fnLongPressStart;
        fnLongPressEnd = _fnLongPressEnd;
        fnShortPress = _fnShortPress;

        pinMode(BUTTON_PIN, INPUT_PULLUP);
    }

    bool can_sleep()
    {
        return tmDown == 0L       // don't sleep while button is down to keep millis counting
               && !fDown && !fUp; // don't sleep if an action is pending
    }

    void sleep()
    {
        LowPower.attachInterruptWakeup(BUTTON_PIN, buttonISR, CHANGE);
    }

    void loop()
    {
        if (fDown)
        {
            Util::setColorRGB(0, 0xFF, 0);
            fDown = false;
            tmDown = millis();
        }
        else if (fUp)
        {
            Util::setColorRGB(0, 0, 0);
            fUp = false;
            if (tmDown && tmDown + SHORT_CLICK_MS < millis())
            {
                // register as UP
                if (fInSwap)
                {
                    fnLongPressEnd();
                    fInSwap = false;
                }
                else
                {
                    fnShortPress();
                }
                tmDown = 0L;
            }
        }
        else if (tmDown && tmDown + LONG_CLICK_MS < millis())
        {
            // in this situation we will not be sleeping, because tmDown is nonzero
            fInSwap = true;
            fnLongPressStart();
        }
    }

}
