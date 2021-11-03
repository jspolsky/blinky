#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.h>

#include "util.h"
#include "ir.h"
#include "pins.h"

namespace IR
{
    IRrecv irrecv(IRRECEIVE_PIN);

    void setup()
    {
        pinMode(IRRECEIVE_PIN, INPUT_PULLUP);
        irrecv.enableIRIn(); // Start the receiver
    }

    void loop()
    {

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
