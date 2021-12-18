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

#define ____ 0
#include "../../hexels/bouncyheart2.h"
#include "../../hexels/_exchange.h"
#include "../../hexels/greyscale.h"
#include "../../hexels/man.h"

namespace Matrix
{
    Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();

#ifdef PREVIEW
    const uint8_t *rgbmp[] = {bmp__exchange, bmp_greyscale};
    const uint8_t rgcframes[] = {cframes__exchange, cframes_greyscale};
#endif

#ifdef BLINKY
    const uint8_t *rgbmp[] = {bmp__exchange, bmp_bouncyheart2, bmp_man};
    const uint8_t rgcframes[] = {cframes__exchange, cframes_bouncyheart2, cframes_man};
#endif

    static bool powerState = false;

    void setup()
    {
        pinMode(MATRIX_ENABLE_PIN, OUTPUT);
        power(true);
        ledmatrix.begin();
    }

    void power(bool bOn)
    {
        if (powerState == false && bOn)
        {
            // turn on
            digitalWrite(MATRIX_ENABLE_PIN, HIGH);
        }
        else if (powerState == true && !bOn)
        {
            // turn off
            digitalWrite(MATRIX_ENABLE_PIN, LOW);
        }

        powerState = bOn;
    }

    void showChar(char c)
    {
        ledmatrix.autoPlayStop();
        ledmatrix.clear();
        ledmatrix.drawChar(0, 0, c, 0x3333, 0x0000, 1);
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
        const uint8_t *pnext = bitmap;

        for (uint8_t frame = 0; frame < cframes; frame++) // write 8 frames then animate
        {
            ledmatrix.setFrame(frame);
            for (int y = 0; y < 9; y++)
                for (int x = 0; x < 16; x += 2)
                {
                    const uint8_t twoNibbles = *pnext++;
                    const uint8_t firstNibble = (twoNibbles & 0xF0) >> 4;
                    const uint8_t secondNibble = (twoNibbles & 0x0F);

                    ledmatrix.drawPixel(15 - x, y, gamma_scale[firstNibble]);
                    ledmatrix.drawPixel(15 - (x + 1), y, gamma_scale[secondNibble]);
                }
        }

        ledmatrix.autoPlay(delay, cframes);
    }

    void displayAnimation(uint16_t code)
    {

        uint8_t const *bitmap = NULL;
        uint8_t cframes = 0;

        if (code == EXCHANGE_ANIMATION)
        {
            bitmap = rgbmp[0];
            cframes = rgcframes[0];
        }
        else if (code < 2)
        {
            bitmap = rgbmp[code + 1];
            cframes = rgcframes[code + 1];
        }
        else if (code >= 2)
        {
            // TODO get more animations. For now show A-Z
            showChar((code % 26) + 'A');
        }

        if (bitmap)
        {
            displayAnimation(cframes, 55, bitmap);
        }
    }
}
