#include "impl.hpp"
// VA 0x4b2500, 146 bytes. Callers include 0x4a2b86, 0x51135c,
// 0x511e4b, 0x512965 and 0x543074; they ignore the machine return register.
void RECORD_THISCALL Record24Storage::append(const void* source) {
    uintptr_t address = reinterpret_cast<uintptr_t>(source);
    const uintptr_t first = reinterpret_cast<uintptr_t>(begin);
    const bool internal = address >= first && address < reinterpret_cast<uintptr_t>(end);
    int32_t index = 0;
    if (internal) {
        // The original uses signed division by 24, truncating toward zero.
        // Even an interior byte address is rounded to a record boundary.
        index = static_cast<int32_t>(static_cast<uint32_t>(address - first)) / 24;
    }
    if (end == capacity_end) grow(end);
    const unsigned char* input = static_cast<const unsigned char*>(source);
    if (internal) input = begin + index * 24;
    if (end) {
        // Preserve the two distinct load/store groups, including overlap effects.
        unsigned char head[16];
        unsigned char tail[8];
        for (unsigned i=0; i<16; ++i) head[i]=input[i];
        for (unsigned i=0; i<16; ++i) end[i]=head[i];
        for (unsigned i=0; i<8; ++i) tail[i]=input[16+i];
        for (unsigned i=0; i<8; ++i) end[16+i]=tail[i];
    }
    // Integer arithmetic retains the observed null-end behavior (0 -> 24).
    end = reinterpret_cast<unsigned char*>(reinterpret_cast<uintptr_t>(end) + 24);
}
