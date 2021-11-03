#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.h>

#include "util.h"
#include "matrix.h"
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

    bool can_sleep()
    {
        return true;
    }

    void sleep()
    {
    }

    void start()
    {
        Util::setColorRGB(0x65, 0x43, 0x21);
        Matrix::displayAnimation(5);

        IrSender.begin(IRSEND_PIN);
        IrSender.sendNEC(0xCFFE, 0x13, 0);

        Matrix::displayAnimation(6);
    }

    void end()
    {
        Util::setColorRGB(0, 0, 0);
        Matrix::displayAnimation(0);
    }
}
