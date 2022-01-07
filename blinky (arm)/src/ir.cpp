#include <Arduino.h>
#include <ArduinoLowPower.h>
#define DECODE_NEC
#include <IRremote.h>

#include "util.h"
#include "matrix.h"
#include "inventory.h"
#include "ir.h"
#include "pins.h"

namespace IR
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

                    IrReceiver.resume();

                } while (msRemaining > 0 && !fReceived);

                IrReceiver.end();
                digitalWrite(IRPOWER_PIN, LOW);
            }

            cLoops++;
            if (cLoops >= 8)
            {
                // Protocol always ends after 8 round trips, which is a few seconds
                done = true;
            }
            else if (fReceived && fAckReceived && cAcksSent >= 2)
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
