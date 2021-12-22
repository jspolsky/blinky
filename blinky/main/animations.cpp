//
// animations
//
// provides the bitmaps for every animation that is available.
//
// Where do animations come from?
//  - there is a folder called ../hexels which has them all
//  - they start out in PNG format
//  - some people use Marmoset Hexels to generate these (available on the steam store)
//  - the PNG is 16 pixels high, with 9 pixels of width for each frame
//  - you run ../parsepng/parsepng.js on the .PNG file to generate a .bytes file which
//    is just the raw bytes needed
//  - these .bytes files are appended onto the binary executable for blinky
//    through the target_add_binary_data directives in CMakeLists.txt
//  - this file, and its header, are responsible for injesting all the animations
//    from the CMakeLists.txt file and providing the bits to the matrix for display.
[[maybe_unused]] static const char *TAG = "animations";

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
}
#include "animations.h"

#define ANIMATION(file) extern const uint8_t file[] asm("_binary_" #file "_bytes_start")

namespace animations
{
    // ADD EACH NEW ANIMATION IN THREE PLACES!
    // 1) in top level CMakeLists.txt
    // 2) with an ANIMATION() declaration, below
    // 3) to the rgAnimations[] array, right below that

    ANIMATION(_exchange);
    ANIMATION(bouncyheart2);
    ANIMATION(man);
    ANIMATION(pong);

    const uint8_t *rgAnimations[] = {
        _exchange,
        bouncyheart2,
        man,
        pong};

    const uint16_t cAnimations = sizeof(rgAnimations) / sizeof(uint8_t *);

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

    uint16_t getAnimationCount()
    {
        return cAnimations;
    }

    uint8_t getAnimationFrameCount(uint16_t animationNumber)
    {
        return rgAnimations[animationNumber % cAnimations][0];
    }

    uint16_t getAnimationDelayMs(uint16_t animationNumber)
    {
        return (rgAnimations[animationNumber % cAnimations][1] << 8) |
               rgAnimations[animationNumber % cAnimations][2];
    }

    // buffer must be 144 bytes
    void getAnimationFrame(uint16_t animationNumber, uint8_t frame, uint8_t *buffer)
    {
        const uint8_t *animationBuf =
            rgAnimations[animationNumber % cAnimations] /* the start of this animation's data */
            + 3                                         /* skip past framecount and delay */
            + (frame * 72);                             /* skip to the frame requested */

        uint8_t *pbuffer = buffer;
        for (int i = 0; i < 72; i++)
        {
            // break out the nibbles
            const uint8_t twoNibbles = animationBuf[i];
            const uint8_t firstNibble = (twoNibbles & 0xF0) >> 4;
            const uint8_t secondNibble = (twoNibbles & 0x0F);

            *pbuffer++ = gamma_scale[firstNibble];
            *pbuffer++ = gamma_scale[secondNibble];
        }
    }
}