#ifndef RIFF_RECORD88_HPP
#define RIFF_RECORD88_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// VA 0x542120, RVA 0x142120, 142 bytes. Field types/names are unknown.
// The caller at 0x5420e0 constructs a range with an 88-byte stride.
// These words preserve representations, including possible pointers/floats;
// no ownership, reference counting, or deep copying is performed.
struct Record88 {
    uint32_t words[22];
    Record88* RIFF_THISCALL copy_construct(const Record88& source);
};
static_assert(sizeof(Record88) == 88, "original record stride");
#endif
