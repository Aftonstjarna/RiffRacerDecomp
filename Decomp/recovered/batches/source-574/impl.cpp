#include "impl.hpp"
// Game.exe VA 0x50dfe0, 56 bytes. ECX=this, one stack argument,
// callee pops 4 bytes. No calls, writes, allocation, or exceptions.
// Callers at 0x50de4f, 0x561806, 0x847e15, 0x851bcf request the
// current size plus insertion count, then allocate the returned capacity.
uint32_t RIFF_THISCALL U32Vector::growth_capacity(uint32_t requested) const {
    const uint32_t byte_distance = limit - begin;
    // Model x86 SAR of the wrapping 32-bit address difference explicitly.
    // This also defines forensic behavior for malformed address triples;
    // those triples do not establish that such vectors are valid containers.
    const uint32_t capacity = (byte_distance >> 2) |
        ((byte_distance & 0x80000000u) ? 0xc0000000u : 0u);
    const uint32_t half = capacity >> 1;
    const uint32_t grown = (0x3fffffffu - half < capacity)
        ? 0u : capacity + half;
    return grown < requested ? requested : grown;
}
