#ifndef RIFF_NARROW_CONSTRUCT_HPP
#define RIFF_NARROW_CONSTRUCT_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Original x86 layout: inline buffer or heap pointer, length +16, capacity +20.
struct NarrowString {
    union Storage { char local[16]; char* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    // Constructor operation exposed as a member to retain the observed EAX=this.
    NarrowString* RIFF_THISCALL construct_terminated(const char* source);
    // Accepted external dependency, VA 0x416520; owns growth/copy/termination.
    NarrowString* RIFF_THISCALL assign_range(const char* source, uint32_t count);
};
#endif
