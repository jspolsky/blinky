#include <Arduino.h>

#include "matrix.h"
#include "util.h"
#include "preview.h"
#define ANIMATION_DATA_BUFFER_SIZE (8 * 9 * 16 / 2) + 2 /* 8*9*16 = max space for animation; 2 for delay */

//
// Blinky can be built in preview mode.
// In preview mode, the parsepng.js program can be used to send
// an animation to the blinky over USB to see what it looks like.
// This requires a USB port, so you need to be using a prototype blinky
// with a QtPy instead of final production blinky hardware.
//

namespace Preview
{

#ifdef PREVIEW
    void setup()
    {
        Serial.begin(9600);
        while (!Serial)
            ;
    }

    void loop()
    {
        static bool waiting_for_cframes = false;
        static bool waiting_for_animation = false;
        static uint8_t cframes = 0;

        static uint8_t animation_data[ANIMATION_DATA_BUFFER_SIZE];
        static size_t animation_data_index = 0;
        static size_t cbWanted = 0;

        if (Serial.available() > 0)
        {

            if (waiting_for_cframes)
            {
                cframes = Serial.read();
                cbWanted = 2 + (cframes * 9 * 16 / 2);
                animation_data_index = 0;
                waiting_for_cframes = false;
                waiting_for_animation = true;
                Util::setColorRGB(255, 0, 0);
            }
            else if (waiting_for_animation)
            {
                Util::setColorRGB(0, 255, 0);
                size_t cbRead = Serial.readBytes((char *)(animation_data + animation_data_index),
                                                 cbWanted - animation_data_index);
                animation_data_index += cbRead;
                if (animation_data_index >= cbWanted)
                {
                    waiting_for_animation = false;
                    uint16_t delay = animation_data[0] * 16 + animation_data[1];
                    Matrix::displayAnimation(cframes, delay, animation_data + 2);
                    Util::setColorRGB(0, 0, 255);
                }
            }
            else
            {
                int b = Serial.read();

                if (b == '?')
                {
                    // for terminal debugging by a human
                    Serial.println("Blinky Preview Ready");
                }
                else if (b == '!')
                {
                    waiting_for_cframes = true;
                }
                else if (b == '#')
                {
                    // ignore. just initializing USB
                    Util::setColorRGB(32, 32, 32);
                }
            }
        }
    }
#endif
}