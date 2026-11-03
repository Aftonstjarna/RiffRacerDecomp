#include "impl.hpp"
// Game.exe 0x416660..0x4166fb: ECX=this, two unsigned stack arguments,
// callee pops 8, EAX=this. No allocation, capacity change, or heap release.
// Callers include self-substring assignment (0x416034/0x41604d) erasing
// a prefix, and graphics options (0x4a289f) erasing one character.
NarrowString* RIFF_THISCALL NarrowString::erase(uint32_t offset, uint32_t count) {
    if (offset > size) {
        narrow_out_of_range("invalid string position");
    }
    const uint32_t remaining = size - offset;
    if (remaining <= count) {
        size = offset;
        char* data = capacity >= 16 ? storage.heap : storage.local;
        data[offset] = 0;
    } else if (count != 0) {
        char* data = capacity >= 16 ? storage.heap : storage.local;
        const uint32_t new_size = size - count;
        // Destination precedes source: forward copy implements this memmove.
        // Original imports memmove at IAT 0x92d4a4; excludes the old NUL.
        for (uint32_t i = offset; i < new_size; ++i) {
            data[i] = data[i + count];
        }
        size = new_size;
        data[new_size] = 0;
    }
    return this;
}
