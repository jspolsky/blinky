#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.h>

#include "util.h"
#include "matrix.h"
#include "inventory.h"
#include "ir.h"
#include "pins.h"

namespace IR
{
    enum IRState
    {
        idle,      // Not doing anything
        sending,   // Button just went down... need to send IR code to peer
        sent,      // Just sent IR code, ready to start receiving
        pausing,   // Just sent IR code, but already received from peer, so pausing before next send
        listening, // Listening for IR codes from peer
    };

    static IRState irstate;
    static unsigned long tmlistening;  // When we started listening
    static unsigned long tmpausing;    // When we started pausing
    static unsigned long msrandomwait; // Random number of ms we back off to listen
    static bool received;              // True when we've received a message and can stop listening
    static bool buttonReleased;        // True when the button has been released
    static unsigned long tmreleased;   // When that happened
    static unsigned long tmstart;      // When we started the protocol

    void setup()
    {
        pinMode(IRPOWER_PIN, OUTPUT);
        digitalWrite(IRPOWER_PIN, LOW);
        irstate = idle;
    }

    void run_protocol()
    {
        buttonReleased = false;
        tmreleased = 0L;
        tmstart = millis();
        Matrix::displayAnimation(EXCHANGE_ANIMATION);
        irstate = sending;

        while (digitalRead(BUTTON_PIN) == LOW)
        {
            loop();
        }

        buttonReleased = true;
        tmreleased = millis();

        while (irstate != idle)
        {
            loop();
        }
    }

    void loop()
    {
        if ((irstate != idle && tmstart + 10000L < millis()) || // end protocol after 10 seconds no matter what
            (buttonReleased && tmreleased + 2000L < millis()))  // end protocol 2 seconds after button released
        {
            // Rather than stopping as soon as the button is
            // released, keep running the protocol for a few
            // seconds so that people can still swap animations
            // when they are having trouble keeping the dang
            // button down

            buttonReleased = false;
            Matrix::displayAnimation(Inventory::getCurrentAnimation());
            if (irstate == listening)
            {
                IrReceiver.end();
                digitalWrite(IRPOWER_PIN, LOW);
            }
            irstate = idle;
        }

        switch (irstate)
        {
        case idle:
            received = false;
            break;

        case sending:
            IrSender.begin(IRSEND_PIN);
            IrSender.sendNEC(0xCFFE, Inventory::getMyAnimation(), 0);

            irstate = sent;
            break;

        case sent:
            if (received)
            {
                // we already have their code, so we don't have to
                // listen. Instead pause 100ms and then send again
                irstate = pausing;
                tmpausing = millis();
            }
            else
            {
                digitalWrite(IRPOWER_PIN, HIGH);
                IrReceiver.begin(IRRECEIVE_PIN);
                irstate = listening;
                randomSeed(tmlistening = millis());
                msrandomwait = 100L + random(500L);
            }
            break;

        case pausing:
            if (tmpausing + 100L < millis())
            {
                irstate = sending;
            }
            break;

        case listening:

            if (IrReceiver.decode() && IrReceiver.decodedIRData.address == 0xCFFE)
            {
                // received!
                received = true;
                IrReceiver.end();
                digitalWrite(IRPOWER_PIN, LOW);

                Matrix::displayAnimation(IrReceiver.decodedIRData.command);
                Inventory::addToInventory(IrReceiver.decodedIRData.command);

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
        return irstate == idle;
    }

    void sleep()
    {
    }

    void start()
    {
    }

    void end()
    {
    }
}
