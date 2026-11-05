#ifndef RIFF_NARROW_ASSIGN_HPP
#define RIFF_NARROW_ASSIGN_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Original 32-bit string layout, as observed in the range helper.
struct NarrowString {
    union Storage { char inline_text[16]; char* heap_text; } storage;
    uint32_t length;
    uint32_t capacity;
    NarrowString* RIFF_THISCALL assign_terminated(const char* source);
    // External dependency at 0x416520; not recovered in this bounded task.
    NarrowString* RIFF_THISCALL assign_range(const char* source, uint32_t count);
};
#endif
