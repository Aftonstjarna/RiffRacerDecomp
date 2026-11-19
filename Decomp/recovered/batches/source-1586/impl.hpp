#ifndef VISUAL_COLOUR_SET_HPP
#define VISUAL_COLOUR_SET_HPP
#include <stdint.h>
// Partial object layout at 0x442f50; names outside the observed fields are unknown.
struct Visual {
    uint8_t unknown0[0x90];
    float colour[4];
    uint8_t unknown_a0[0xd0];
    uint32_t flags;
    void set_colour(const float* value);
};
#endif
