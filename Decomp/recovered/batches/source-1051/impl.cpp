#include "impl.hpp"
// Game.exe VA 0x5a95f0, RVA 0x1a95f0, 72 bytes. ECX=this,
// one unsigned stack argument, callee pops 4 bytes; EAX is the result.
// Caller 0x5a93a8 requests size+insert_count after a length check, then
// passes the result to allocator 0x5a9640, which multiplies by 12.
uint32_t RECORD12_THISCALL Record12Vector::capacity_growth(uint32_t minimum) const {
    const uint32_t bytes = capacity_end - begin;
    // Interpret the wrapped x86 subtraction as signed without relying on
    // out-of-range unsigned-to-signed conversion or C++ pointer subtraction.
    const int32_t signed_bytes = bytes <= 0x7fffffffu
        ? static_cast<int32_t>(bytes)
        : -1 - static_cast<int32_t>(~bytes);
    const uint32_t capacity = static_cast<uint32_t>(signed_bytes / 12);
    const uint32_t half = capacity >> 1;
    // Preserve the unsigned compare and zero fallback, even for malformed
    // headers. The requested minimum itself is not clamped or validated.
    const uint32_t grown = (0x15555555u - half < capacity)
        ? 0u : capacity + half;
    return grown < minimum ? minimum : grown;
}
