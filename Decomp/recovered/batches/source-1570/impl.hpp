#ifndef FONT_ADVANCE_HPP
#define FONT_ADVANCE_HPP
#include <stdint.h>

// 32-bit original layouts; unknown bytes deliberately remain unnamed.
struct FontGlyph {
    uint16_t code;
    uint8_t unknown[0x22];
    float advance;
    uint8_t tail[4];
};
struct Font {
    uint8_t unknown0[0x28];
    FontGlyph *begin;
    FontGlyph *end;
    uint8_t unknown30[4];
    FontGlyph *fallback;
    FontGlyph line_break;
    uint8_t unknown64[4];
    Font *alternate;
    float advance_utf16(const uint16_t *text);
};
#endif
