#include <Arduino.h>
#include <Adafruit_IS31FL3731.h>

#include "pins.h"
#include "inventory.h"
#include "matrix.h"
#include "util.h"

// The lookup table to make the brightness changes be more visible
// Limiting max brightness to save battery and because 47 is still
// pretty bright
const uint8_t gamma_scale[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    8,
    10,
    12,
    15,
    19,
    24,
    30,
    37,
    47,
};

namespace Matrix
{
    Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();

#define ____ 0
#include "../../hexels/_exchange.h"
#include "../../hexels/greyscale.h"

#ifdef PREVIEW
    const uint8_t *rgbmp[] = {bmp__exchange, bmp_greyscale};
#endif

#ifdef BLINKY

#include "../../hexels/bouncyheart2.h"
#include "../../hexels/man.h"
#include "../../hexels/pong.h"
    // ADD ADDITIONAL .h FILES ABOVE

    const uint8_t *rgbmp[] = {
        bmp__exchange,
        bmp_bouncyheart2,
        bmp_man,
        bmp_pong,
        // ADD ADDITIONAL ANIMATIONS ABOVE
    };

#endif

    const size_t cAnimations = sizeof(rgbmp) / sizeof(uint8_t *);

    size_t getAnimationCount() { return cAnimations - 1; };

    static bool powerState = false;

    void setup()
    {
        pinMode(MATRIX_ENABLE_PIN, OUTPUT);
        power(true);
        ledmatrix.begin();
    }

    bool isPowerOn()
    {
        return powerState;
    }

    void power(bool bOn)
    {
        if (powerState == false && bOn)
        {
            // turn on
            digitalWrite(MATRIX_ENABLE_PIN, HIGH);
            ledmatrix.begin();
        }
        else if (powerState == true && !bOn)
        {
            // turn off
            digitalWrite(MATRIX_ENABLE_PIN, LOW);
        }

        powerState = bOn;
    }

    // void showGreyscale16(uint8_t v)
    // {

    //     // v is 0 (black) to 15 (white)
    //     ledmatrix.autoPlayStop();

    //     for (int y = 0; y < 9; y++)
    //         for (int x = 0; x < 16; x++)
    //             ledmatrix.drawPixel(15 - x, y, gamma_scale[v]);
    // }

    void displayAnimation(uint8_t cframes, uint16_t delay, uint8_t const *bitmap)
    {
        ledmatrix.shutdown(1);
        const uint8_t *pnext = bitmap;

        for (uint8_t frame = 0; frame < cframes; frame++) // write 8 frames then animate
        {
            ledmatrix.setFrame(frame);

            uint8_t frameBuffer[145];
            uint8_t *pframeBuffer = frameBuffer;
            *pframeBuffer++ = 0;

            for (int i = 0; i < 72; i++)
            {
                const uint8_t twoNibbles = *pnext++;
                const uint8_t firstNibble = (twoNibbles & 0xF0) >> 4;
                const uint8_t secondNibble = (twoNibbles & 0x0F);

                *pframeBuffer++ = gamma_scale[firstNibble];
                *pframeBuffer++ = gamma_scale[secondNibble];
            }

            ledmatrix.drawEntireFrame(frameBuffer);
        }

        ledmatrix.shutdown(0);
        ledmatrix.autoPlay(delay, cframes);
    }

    void displayAnimation(uint16_t code)
    {

        // code is actually one less than the position in the array
        // 0xFFFF is the exchange animation, located at position 0 in rgbmp
        // 0 is the first animation, located at position 1 in rgbmp
        //
        size_t position = (code == EXCHANGE_ANIMATION) ? 0 : code + 1;

        if (position >= cAnimations)
        {
            return;
        }

        uint8_t const *bitmap = rgbmp[position] + 3;
        uint8_t cframes = rgbmp[position][0];
        uint16_t delay = (rgbmp[position][1] << 8) | (rgbmp[position][2]);

        power(true);
        displayAnimation(cframes, delay, bitmap);
    }

    void testPattern()
    {
        uint8_t buf[145];
        buf[0] = 0;

        for (int i = 1; i <= 144; i++)
        {
            buf[i] = i + 10;
        }
        ledmatrix.drawEntireFrame(buf);
        delay(1000);

        for (int i = 1; i <= 144; i++)
        {
            buf[145 - i] = i + 10;
        }
        ledmatrix.drawEntireFrame(buf);
        delay(1000);
    }
}
