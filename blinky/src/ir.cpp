#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.h>

#include "util.h"
#include "matrix.h"
#include "ir.h"
#include "pins.h"

namespace IR
{
    enum IRState
    {
        idle,     // Not doing anything
        starting, // Button just went down... need to SEND
    };

    static IRState irstate;

    // IRrecv irrecv(IRRECEIVE_PIN);

    void setup()
    {
        irstate = idle;

        // pinMode(IRRECEIVE_PIN, INPUT_PULLUP);
        // irrecv.enableIRIn(); // Start the receiver
    }

    void loop()
    {
        switch (irstate)
        {
        case idle:
            break;

        case starting:
            Matrix::displayAnimation(5);

            IrSender.begin(IRSEND_PIN);
            IrSender.sendNEC(0xCFFE, 0x13, 0);

            Matrix::displayAnimation(6);
            irstate = idle;
            break;

        default:
            break;
        }

        // if (irrecv.decode())
        // {
        //     if (irrecv.decodedIRData.address == 0xCFFE)
        //     {
        //         // it's for us!
        //         Util::setColorHSV(irrecv.decodedIRData.command);
        //     }

        //     IrReceiver.resume();
        // }
    }

    bool can_sleep()
    {
        return true;
    }

    void sleep()
    {
    }

    void start()
    {
        irstate = starting;
    }

    void end()
    {
        Util::setColorRGB(0, 0, 0);
        Matrix::displayAnimation(0);
        irstate = idle;
    }
}
