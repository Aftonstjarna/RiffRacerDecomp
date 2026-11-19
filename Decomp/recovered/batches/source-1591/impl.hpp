#ifndef TEXT_COLOUR_FORWARD_HPP
#define TEXT_COLOUR_FORWARD_HPP
#include <stdint.h>

// Partial 32-bit layouts. Helper implementations are separate dependencies.
struct Visual {
    uint8_t unknown[0x174];
    void set_colour(const float* colour);
};
struct TextItem {
    uint8_t unknown00[0x10];
    uint32_t kind;
    uint8_t unknown14[0x40];
    float colour[4];
    uint8_t unknown64[0x120];
    void* entries_begin;
    void* entries_end;
    uint8_t unknown18c[0x38];
    Visual* visual;
    void set_base_colour(const float* colour);
    void set_colour(const float* colour);
};
#endif
