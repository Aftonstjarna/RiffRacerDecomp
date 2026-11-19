#include "impl.hpp"

// Original VA 0x456e60, x86 thiscall. The secondary's own fallback and
// secondary pointer are deliberately not consulted.
GlyphRecord* FontLookup::lookup(uint16_t character, uint8_t* used_secondary) {
    if (used_secondary) *used_secondary = 0;
    if (character == 13 || character == 10) return &line_break;
    for (GlyphRecord* glyph = begin; glyph != end; ++glyph) {
        if (glyph->character == character) return glyph;
    }
    if (used_secondary && secondary) {
        for (GlyphRecord* glyph = secondary->begin; glyph != secondary->end; ++glyph) {
            if (glyph->character == character) {
                *used_secondary = 1;
                return glyph;
            }
        }
    }
    return fallback;
}
