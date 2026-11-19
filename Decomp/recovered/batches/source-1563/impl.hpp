#ifndef FONT_GLYPH_LOOKUP_HPP
#define FONT_GLYPH_LOOKUP_HPP
#include <stdint.h>

// Layouts observed in the 32-bit original; unknown bytes remain opaque.
struct GlyphRecord {
    uint16_t character;
    uint8_t unknown[42];
};
struct FontLookup {
    uint8_t unknown00[0x28];
    GlyphRecord* begin;
    GlyphRecord* end;
    uint8_t unknown30[4];
    GlyphRecord* fallback;
    GlyphRecord line_break;
    uint8_t unknown64[4];
    FontLookup* secondary;
    GlyphRecord* lookup(uint16_t character, uint8_t* used_secondary);
};
#endif
