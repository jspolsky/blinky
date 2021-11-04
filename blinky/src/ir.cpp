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
        sending,   // Button just went down... need to send IR code to peer
        sent,      // Just sent IR code, ready to start receiving
        listening, // Listening for IR codes from peer
    };

    static IRState irstate;
    static unsigned long tmlistening;  // When we started listening
    static unsigned long msrandomwait; // Random number of ms we back off to listen
    static bool received;              // True when we've received a message and can stop listening

    void setup()
    {
        pinMode(IRPOWER_PIN, OUTPUT);
        digitalWrite(IRPOWER_PIN, LOW);
        irstate = idle;
    }

    void loop()
    {
        switch (irstate)
        {
        case idle:
            received = false;
            break;

        case sending:
            Matrix::displayAnimation(1);

            IrSender.begin(IRSEND_PIN);
            IrSender.sendNEC(0xCFFE, 0x13, 0);

            irstate = sent;
            break;

        case sent:
            Matrix::displayAnimation(2);

            if (received)
            {
                // once we have received peer's animation, we will
                // continue to transmit every 100 ms
                delay(100);
                irstate = sending;
            }
            else
            {
                digitalWrite(IRPOWER_PIN, HIGH);
                IrReceiver.begin(IRRECEIVE_PIN);
                irstate = listening;
                randomSeed(tmlistening = millis());
                msrandomwait = 300L + random(300L);

                Matrix::displayAnimation(3);
            }
            break;

        case listening:

            if (IrReceiver.decode() && IrReceiver.decodedIRData.address == 0xCFFE)
            {
                // received!
                received = true;
                Util::setColorHSV(IrReceiver.decodedIRData.command);
                IrReceiver.end();
                digitalWrite(IRPOWER_PIN, LOW);
                irstate = sending;
            }
            else
            {
                // Have we been listening long enough?
                // Send again.
                if (tmlistening + msrandomwait < millis())
                {
                    IrReceiver.end();
                    digitalWrite(IRPOWER_PIN, LOW);
                    irstate = sending;
                }
                else
                {
                    IrReceiver.resume();
                }
            }
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
        irstate = sending;
    }

    void end()
    {
        Util::setColorRGB(0, 0, 0);
        Matrix::displayAnimation(0);
        if (irstate == listening)
        {
            IrReceiver.end();
            digitalWrite(IRPOWER_PIN, LOW);
        }
        irstate = idle;
    }
}
