#ifndef RIFF_NARROW_MOVE_HPP
#define RIFF_NARROW_MOVE_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Original x86 layout: inline bytes / heap pointer at +0, length +16,
// capacity +20. Heap pointers retain their native type for a Linux port.
struct NarrowString {
    union Storage { unsigned char local[16]; unsigned char* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    NarrowString* RIFF_THISCALL move_construct(NarrowString* source);
};
static_assert(sizeof(NarrowString) == 24, "string layout");
#endif
