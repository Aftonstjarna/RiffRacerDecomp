#include "impl.hpp"
// Game.exe VA 0x44f9b0..0x44faa6, ECX=this, RET 8, EAX=this.
// Direct callers at 0x44f4d5 and 0x44f6e4 pass (end-begin)/2;
// 0x44f6b7 explicitly passes zero; 0x55e826 passes a literal and 27 units.
// Unsigned address comparisons reproduce the x86 alias test without relational
// comparison/subtraction of unrelated C++ pointers. Valid string storage is
// assumed; integer wrap and odd-byte interior pointers follow original x86.
WideString* RIFF_THISCALL WideString::assign_range(const uint16_t* source, uint32_t count) {
    if (source) {
        const uintptr_t base = reinterpret_cast<uintptr_t>(capacity < 8 ? storage.local : storage.heap);
        const uintptr_t address = reinterpret_cast<uintptr_t>(source);
        const uintptr_t end = base + static_cast<uintptr_t>(length) * 2u;
        if (address >= base && address < end) {
            // Original SAR by one rounds an odd interior byte address down.
            return assign_substring(this, static_cast<uint32_t>((address-base)/2u), count);
        }
    }
    if (count > 0x7ffffffeu) wide_length_error("string too long");
    if (capacity < count) {
        grow(count, length);
        if (!count) return this; // Retained original post-growth zero arm.
    } else if (!count) {
        length = 0;
        (capacity < 8 ? storage.local : storage.heap)[0] = 0;
        return this;
    }
    uint16_t* destination = capacity < 8 ? storage.local : storage.heap;
    if (count) wide_copy(destination, source, count * 2u);
    length = count;
    // Re-read storage selection, as the original does after the copy call.
    (capacity < 8 ? storage.local : storage.heap)[count] = 0;
    return this;
}
