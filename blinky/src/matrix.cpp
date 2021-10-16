#include <Arduino.h>
#include <Adafruit_IS31FL3731.h>

#include "matrix.h"

// The lookup table to make the brightness changes be more visible
const uint8_t gamma_scale[] = {0, 1, 2, 4,
                               6, 10, 13, 18,
                               22, 28, 33, 39,
                               46, 53, 61, 69};

#define ____ 0
#include "../../hexels/bouncyheart.h"

namespace Matrix
{
    Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();

    void setup()
    {
        if (!ledmatrix.begin())
        {
            Serial.println("IS31 not found");
            while (1)
                ;
        }
    }

    void showChar(char c)
    {
        ledmatrix.autoPlayStop();
        ledmatrix.drawChar(0, 0, c, 0x3333, 0x0000, 1);
    }

    void displayAnimation(uint16_t code)
    {
        // UNDONE have more animations
        // for now there is just one (0)
        // everything else displays as an ASCII thing

        if (code == 0)
        {
            const uint8_t *pnext = a; // UNDONE 'a' is the only animation i have right now

            for (uint8_t frame = 0; frame < 8; frame++) // write 8 frames then animate
            {
                ledmatrix.setFrame(frame);
                for (int x = 0; x < 16; x++)
                    for (int y = 0; y < 9; y++)
                        ledmatrix.drawPixel(15 - x, y, gamma_scale[(*pnext++) >> 4]);
            }

            ledmatrix.autoPlay(55);
        }
        else
        {
            // TODO get more animations. For now show A-Z
            showChar((code % 26) + 'A' - 1);
        }
    }

}
