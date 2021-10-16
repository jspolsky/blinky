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

    const unsigned long SHORT_CLICK_MS = 10L;  // how long button must be pressed to read a short click
    const unsigned long LONG_CLICK_MS = 1000L; // how long button must be pressed to read a long click

    void buttonISR()
    {
        int state = digitalRead(BUTTON_PIN);
        fDown = (state == LOW);
        fUp = (state == HIGH);
    }

    void setup()
    {
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
                    fnEndSwap();
                    fInSwap = false;
                }
                else
                {
                    fnSwitch();
                }
                tmDown = 0L;
            }
        }
        else if (tmDown && tmDown + LONG_CLICK_MS < millis())
        {
            // in this situation we will not be sleeping, because tmDown is nonzero
            fInSwap = true;
            fnStartSwap();
        }
    }

    void fnStartSwap()
    {
        Util::setColorRGB(0x65, 0x43, 0x21);
        Matrix::displayAnimation(1);
    }

    void fnEndSwap()
    {
        Util::setColorRGB(0, 0, 0);
        Matrix::displayAnimation(2);
    }

    void fnSwitch()
    {
        Util::setColorRGB(0, 0, 0xFF);
        Matrix::displayAnimation(0);
    }
}
