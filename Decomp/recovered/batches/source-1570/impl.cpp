#include "impl.hpp"

// VA 0x456450, x86 thiscall. Code units are searched independently; CR and
// LF each use the embedded glyph. Alternate lookup is only one level deep.
float Font::advance_utf16(const uint16_t *text) {
    if (!text) return 0.0f;
    float total = 0.0f;
    const bool use_alternate = alternate != 0;
    while (*text) {
        uint16_t code = *text++;
        FontGlyph *glyph;
        if (code == 13 || code == 10) {
            glyph = &line_break;
        } else {
            glyph = begin;
            while (glyph != end && glyph->code != code) ++glyph;
            if (glyph == end) {
                glyph = 0;
                if (use_alternate && alternate) {
                    glyph = alternate->begin;
                    while (glyph != alternate->end && glyph->code != code) ++glyph;
                    if (glyph == alternate->end) glyph = 0;
                }
                if (!glyph) glyph = fallback;
            }
        }
        total += glyph->advance;
    }
    return total;
}
