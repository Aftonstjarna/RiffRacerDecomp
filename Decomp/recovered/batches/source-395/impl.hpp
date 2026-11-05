#ifndef RIFF_NARROW_APPEND_HPP
#define RIFF_NARROW_APPEND_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif

// 32-bit original narrow-string layout, supported by append_range at 0x442170.
// Storage contains either 16 inline bytes or a pointer in its first word.
struct NarrowString {
    union Storage { char local[16]; char* heap; } storage;
    uint32_t size;
    uint32_t capacity;

    NarrowString* RIFF_THISCALL append_terminated(const char* text);
    // Existing dependency, deliberately not recovered in this bounded task.
    // The port must supply the original range-append behavior, including aliases,
    // growth, length errors and its returned pointer. Test.cpp supplies an adapter.
    NarrowString* RIFF_THISCALL append_range(const char* text, uint32_t count);
};
#endif
