#ifndef RIFF_NARROW_SUBSTRING_CONSTRUCT_HPP
#define RIFF_NARROW_SUBSTRING_CONSTRUCT_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
// Original x86 layout: inline/heap union + size at 16 + capacity at 20.
// Capacity >=16 selects heap storage; capacity excludes the terminator.
struct NarrowString {
    union Storage { char local[16]; char* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    NarrowString* RIFF_THISCALL construct_substring(NarrowString* destination,
                                                   uint32_t offset, uint32_t count) const;
    // Existing assignment dependency, VA 0x415fe0. Not recovered in this task.
    // A port must supply its allocation, range-error and string-copy semantics.
    NarrowString* RIFF_THISCALL assign_substring(const NarrowString* source,
                                                uint32_t offset, uint32_t count);
};
static_assert(sizeof(NarrowString)==24, "original layout requires 32-bit pointers");
#endif
