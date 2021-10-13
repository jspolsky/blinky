#include <Arduino.h>
#include <ArduinoLowPower.h>
#include "util.h"
#include "button.h"
#include "pins.h"

#define debounceDelay 50

namespace Button
{
    bool zToggle = 0;
    volatile uint8_t buttonPressed = 0; // changes to 1 when the interrupt fires
    volatile unsigned long button_time = 0;
    volatile unsigned long last_button_time = 0;

    void buttonPressISR()
    {
        // UNDONE BUTTON DEBOUNCING IS INTERFERING WITH SLEEP

        // unsigned long button_time = millis();
        // if (button_time - last_button_time > debounceDelay)
        // {
        buttonPressed = 1;
        //     last_button_time = button_time;
        // }
    }

    void setup()
    {
        pinMode(BUTTON_PIN, INPUT_PULLUP);
    }

    void sleep()
    {
        LowPower.attachInterruptWakeup(BUTTON_PIN, buttonPressISR, FALLING);
    }

    void loop()
    {

        if (buttonPressed)
        {
            zToggle = !zToggle;
            if (zToggle)
                Util::setColorRGB(0, 0xAF, 0);
            else
                Util::setColorRGB(0xAF, 0, 0xAF);

            buttonPressed = false;
        }
    }
}
