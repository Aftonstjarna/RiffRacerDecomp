#include "impl.hpp"

// Reviewed against original 0x44f8f0..0x44f9a0 and callers 0x450003,
// 0x535f48, 0x55e1ba: unused iterator/debug argument then one WCHAR.
// The helper may change length and storage, so read both again after growth.
WideString* RIFF_THISCALL WideString::append_char(uint32_t, uint16_t character) {
    const uint32_t old_length = length;
    if (UINT32_MAX - old_length <= 1u)
        wide_string_length_error("string too long");
    const uint32_t new_length = old_length + 1u;
    if (new_length > 0x7ffffffeu)
        wide_string_length_error("string too long");

    if (capacity < new_length) {
        grow(new_length, old_length);
        if (new_length == 0u)
            return this;
    } else if (new_length == 0u) {
        // Retained original zero-length arm; unreachable if error is nonreturning.
        length = 0;
        if (capacity < 8u) storage.inline_text[0] = 0;
        else storage.heap_text[0] = 0;
        return this;
    }

    uint16_t* text = capacity < 8u ? storage.inline_text : storage.heap_text;
    text[length] = character;
    length = new_length;
    text = capacity < 8u ? storage.inline_text : storage.heap_text;
    text[new_length] = 0;
    return this;
}
