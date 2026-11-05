#include "impl.hpp"
// Game.exe VA 0x543310..0x543359, ECX=this, RET 4.
// Caller 0x5433a0 passes size + insertion count at 0x54341b, then uses
// the result with allocator 0x543360 (24 bytes/record, max 0x0aaaaaaa).
// The helper itself does not enforce required <= max and has no side effects.
uint32_t RIFF_THISCALL Record24Storage::growth_capacity(uint32_t required) const {
    const uint32_t distance = allocation_end - begin;
    // Interpret the wrapped subtraction as signed without relying on an
    // implementation-defined unsigned-to-signed conversion or pointer UB.
    const int32_t signed_distance = distance <= 0x7fffffffu
        ? static_cast<int32_t>(distance)
        : -1 - static_cast<int32_t>(0xffffffffu - distance);
    const uint32_t capacity = static_cast<uint32_t>(signed_distance / 24);
    const uint32_t half = capacity >> 1;
    uint32_t candidate = 0;
    // Unsigned subtraction and comparison deliberately mirror the original,
    // including malformed triples; this is not a saturating max-size clamp.
    if (0x0aaaaaaau - half >= capacity)
        candidate = capacity + half;
    return candidate < required ? required : candidate;
}
