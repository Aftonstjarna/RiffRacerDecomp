#include "impl.hpp"
namespace recovered {
// Game.exe VA 0x58eab0, 77 bytes; original MSVC i386 thiscall, no arguments.
// Callers at 0x58f518 and 0x58fa84 store EAX at object+0x6d38.
// Three accessible bytes are required even when bit_offset == 0. No refill,
// length check, allocation, imports, or exception registration occurs here.
uint32_t AudioBitstream::read16() {
    const uint8_t* bytes = cursor;
    const uint32_t offset = bit_offset;
    const uint32_t window = (uint32_t(bytes[0]) << 16) |
                            (uint32_t(bytes[1]) << 8) | uint32_t(bytes[2]);
    const uint32_t shifted = window << (offset & 31u);
    const uint32_t next = offset + 16u;
    // Explicit SAR semantics avoid signed overflow and negative right shifts.
    const int32_t advance = (next & 0x80000000u)
        ? -static_cast<int32_t>((~next) >> 3) - 1
        : static_cast<int32_t>(next >> 3);
    bit_offset = next & 7u;
    cursor = reinterpret_cast<const uint8_t*>(
        reinterpret_cast<uintptr_t>(bytes) + static_cast<uintptr_t>(advance));
    return (shifted & 0x00ffffffu) >> 8;
}
}
