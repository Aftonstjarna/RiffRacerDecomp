#include "impl.hpp"
// Game.exe VA 0x44fd30, 165 bytes. ECX=this, stack position/count,
// EAX=this, RET 8. Caller 0x44fb6f erases a prefix after truncating a
// self-substring assignment. Layout is 16-byte small buffer, length, capacity.
WideString* RIFF_THISCALL WideString::erase(uint32_t position, uint32_t count) {
    if (position > size) {
        // Original nonreturning import: [0x92d16c], message 0x99995c.
        wide_out_of_range("invalid string position");
    }
    const uint32_t remaining = size - position;
    if (remaining <= count) {
        size = position;
        uint16_t* data = capacity < 8 ? storage.local : storage.heap;
        data[position] = 0;
    } else if (count != 0) {
        uint16_t* data = capacity < 8 ? storage.local : storage.heap;
        const uint32_t new_size = size - count;
        // Original memmove import [0x92d4a4] copies only the surviving suffix,
        // excluding its terminator. Leftward overlapping moves permit this loop.
        for (uint32_t i = position; i < new_size; ++i) {
            data[i] = data[i + count];
        }
        size = new_size;
        data[new_size] = 0;
    }
    // No allocation/free, capacity change, or clearing of the erased tail.
    return this;
}
