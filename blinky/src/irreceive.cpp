#include <Arduino.h>
#include <ArduinoLowPower.h>
#define DECODE_NEC
#include <IRremote.h>

#include "util.h"
#include "irreceive.h"
#include "pins.h"

#define debounceDelay 50

namespace Irreceive
{
    IRrecv irrecv(IRRECEIVE_PIN);
    volatile uint8_t irActivity = 0; // changes to 1 when the interrupt fires

    void irActivityISR()
    {
        // woken up by ir
        irActivity = 1;
    }

    void setup()
    {
        pinMode(IRRECEIVE_PIN, INPUT_PULLUP);
        LowPower.attachInterruptWakeup(A1, irActivityISR, FALLING);
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
