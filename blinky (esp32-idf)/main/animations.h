#pragma once

namespace animations
{
    uint16_t getAnimationCount();
    uint8_t getAnimationFrameCount(uint16_t animationNumber);
    uint16_t getAnimationDelayMs(uint16_t animationNumber);
    void getAnimationFrame(uint16_t animationNumber, uint8_t frame, uint8_t *buffer); // buffer must be 144 bytes
}