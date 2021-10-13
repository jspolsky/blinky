#include <Arduino.h>
#include <ArduinoLowPower.h>
#define DECODE_NEC
#include <IRremote.h>

#include "util.h"
#include "irreceive.h"
#include "pins.h"

#define debounceDelay 50
#define msStayAwake 200 /* how long to stay awake after irActivity */

namespace Irreceive
{
    IRrecv irrecv(IRRECEIVE_PIN);
    volatile uint8_t irActivity = 0; // changes to 1 when the interrupt fires
    volatile bool fCanSleep = true;  // true when it's OK for the MCU to go to low power/sleep mode
    volatile uint32_t msNextSleepTime = 0;

    void irActivityISR()
    {
        // woken up by ir
        irActivity = 1;
        fCanSleep = false;
        msNextSleepTime = millis() + msStayAwake;
    }

    bool can_sleep()
    {
        if (msNextSleepTime && millis() > msNextSleepTime)
        {
            fCanSleep = true;
        }

        return fCanSleep;
    }

    void sleep()
    {
        LowPower.attachInterruptWakeup(IRRECEIVE_PIN, irActivityISR, FALLING);
    }

    void setup()
    {
        pinMode(IRRECEIVE_PIN, INPUT_PULLUP);
        pinMode(IRRECEIVE_VCC_PIN, OUTPUT);
        digitalWrite(IRRECEIVE_VCC_PIN, HIGH);
    }

    void loop()
    {
        if (irActivity)
        {
            irrecv.enableIRIn(); // Start the receiver
            irActivity = false;
        }

        if (irrecv.decode())
        {
            if (irrecv.decodedIRData.address == 0xCFFE)
            {
                // it's for us!
                Util::setColorHSV(irrecv.decodedIRData.command);
            }

            IrReceiver.resume();
        }
    }
}
