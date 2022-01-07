#include <Arduino.h>
#include <ArduinoLowPower.h>
#include "button.h"
#include "pins.h"
#include "matrix.h"
#include "inventory.h"
#include "ir.h"

namespace Button
{
    volatile bool fDown = false;

    void isrPin()
    {
        fDown = (digitalRead(BUTTON_PIN) == LOW);
    }

    void setup()
    {
        fDown = false;
        pinMode(BUTTON_PIN, INPUT_PULLUP);
        LowPower.attachInterruptWakeup(digitalPinToInterrupt(BUTTON_PIN), isrPin, CHANGE);
    }

    void loop()
    {
        if (fDown)
        {

            fDown = false;

            unsigned long tmStart = millis();
            bool fLongPressDetected = false;

            // wait for up
            while (digitalRead(BUTTON_PIN) == LOW)
            {

                if (tmStart + 500L < millis())
                {
                    fLongPressDetected = true;
                    IR::run_protocol();
                }

                LowPower.idle(50);
            }

            if (!fLongPressDetected)
            {
                Matrix::displayAnimation(
                    Matrix::isPowerOn() ? Inventory::nextAnimation()
                                        : Inventory::getCurrentAnimation());
            }
        }
    }

}
