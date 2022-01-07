#include <Arduino.h>
#include <ArduinoLowPower.h>
#define DECODE_NEC
#include <IRremote.h>

#include "util.h"
#include "matrix.h"
#include "inventory.h"
#include "ir.h"
#include "pins.h"

namespace IR2
{
    // new and improved IR protocol

    void setup()
    {
        pinMode(IRPOWER_PIN, OUTPUT);
        digitalWrite(IRPOWER_PIN, LOW);
    }

    void run_protocol()
    {
        const uint16_t ADDRESS = 0xCFB0;
        const uint16_t ADDRESS_WITH_ACK = 0xCFB1;

        bool fReceived = false;    // we have recevied their code
        uint8_t cAcksSent = 0;     // if fReceived, how many times we have sent an ACK
        bool fAckReceived = false; // we know that they have received our code
        uint8_t cLoops = 0;        // how many times we've attempted to send/receive

        randomSeed(millis());
        Matrix::displayAnimation(EXCHANGE_ANIMATION);

        bool done = false;
        while (!done)
        {
            //
            // SEND OUR CODE TO PEER
            //

            uint16_t address;
            if (fReceived)
            {
                address = ADDRESS_WITH_ACK;
                cAcksSent++;
            }
            else
            {
                address = ADDRESS;
            }
            IrSender.begin(IRSEND_PIN);
            IrSender.sendNEC(address, Inventory::getMyAnimation(), 0);

            //
            // LISTEN FOR CODE FROM PEER
            //

            if (fReceived && fAckReceived)
            {
                LowPower.deepSleep(300);
            }
            else
            {
                //
                // We listen for a random amount of time between 100 and 600 ms
                // before sending again. The amount is random to prevent two
                // blinkys getting into a situation where both are sending
                // at exactly the same time.
                //
                signed long msRemaining = 100L + random(500L);

                digitalWrite(IRPOWER_PIN, HIGH);
                IrReceiver.begin(IRRECEIVE_PIN);
                do
                {
                    LowPower.idle(50);
                    msRemaining -= 50;

                    if (IrReceiver.decode() && (IrReceiver.decodedIRData.address == ADDRESS ||
                                                IrReceiver.decodedIRData.address == ADDRESS_WITH_ACK))
                    {
                        if (!fReceived)
                        {
                            Matrix::displayAnimation(IrReceiver.decodedIRData.command);
                            Inventory::addToInventory(IrReceiver.decodedIRData.command);
                            fReceived = true;
                        }
                        fAckReceived = (IrReceiver.decodedIRData.address == ADDRESS_WITH_ACK);
                    }
                } while (msRemaining > 0 && !fReceived);

                IrReceiver.end();
                digitalWrite(IRPOWER_PIN, LOW);
            }

            cLoops++;
            if (cLoops > 8)
            {
                // Protocol always ends after 8 round trips, which is a few seconds
                done = true;
            }
            else if (fReceived && fAckReceived && cAcksSent > 2)
            {
                done = true;
            }
        };

        if (!fReceived)
        {
            Matrix::displayAnimation(Inventory::getCurrentAnimation());
        }
    }
}

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
                    LowPower.idle(50);
                }
            }
            break;

        default:
            break;
        }
    }

}
