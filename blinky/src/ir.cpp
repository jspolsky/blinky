#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.h>

#include "util.h"
#include "matrix.h"
#include "ir.h"
#include "pins.h"

// TODO  Run the power for the IR receiver off of a pin to minimize idle consumption

namespace IR
{
    enum IRState
    {
        idle,      // Not doing anything
        starting,  // Button just went down... need to send IR code to peer
        sent,      // Just sent IR code, ready to start receiving
        listening, // Listening for IR codes from peer
    };

    static IRState irstate;

    void setup()
    {
        irstate = idle;
    }

    void loop()
    {
        switch (irstate)
        {
        case idle:
            break;

        case starting:
            Matrix::displayAnimation(1);

            IrSender.begin(IRSEND_PIN);
            IrSender.sendNEC(0xCFFE, 0x13, 0);

            irstate = sent;
            break;

        case sent:
            Matrix::displayAnimation(2);

            IrReceiver.begin(IRRECEIVE_PIN);

            irstate = listening;
            break;

        case listening:
            Matrix::displayAnimation(3);

            if (IrReceiver.decode())
            {
                if (IrReceiver.decodedIRData.address == 0xCFFE)
                {
                    // received!
                    Util::setColorHSV(IrReceiver.decodedIRData.command);
                }
            }
            IrReceiver.resume();
            break;

        default:
            break;
        }
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
