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

        // Write all 8 frames

        const uint8_t *pnext = a;

        for (uint8_t frame = 0; frame < 8; frame++)
        {
            ledmatrix.setFrame(frame);
            for (int x = 0; x < 16; x++)
                for (int y = 0; y < 9; y++)
                    ledmatrix.drawPixel(15 - x, y, gamma_scale[(*pnext++) >> 4]);
        }

        ledmatrix.autoPlay(125);
    }
}
