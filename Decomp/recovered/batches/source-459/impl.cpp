#include "impl.hpp"
// Game.exe VA [0x415b00,0x415b51), RVA 0x15b00, ECX=this, ret 4.
// Callers 0x4307b0 / 0x4307ce pass an output object in ECX and a literal
// pointer on the stack. This initializes storage; it does not destroy an old
// allocation. Only local[0] is cleared; the other 15 bytes are left alone.
// Initialization precedes scanning, including when source aliases the object.
// source must point at readable NUL-terminated memory; no null guard exists.
NarrowString* RIFF_THISCALL NarrowString::construct_terminated(const char* source) {
    capacity = 15;
    length = 0;
    storage.local[0] = '\0';
    uint32_t count = 0;
    if (*source != '\0') {
        const char* end = source;
        do { ++end; } while (end[-1] != '\0');
        count = static_cast<uint32_t>(end - (source + 1));
    }
    assign_range(source, count);
    return this; // The original discards the helper's EAX.
}
