#ifndef RIFF_RECORD24_GROWTH_HPP
#define RIFF_RECORD24_GROWTH_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Original 32-bit address words, not native pointers. No pointees are accessed.
// Names describe the vector layout inferred from the insertion caller.
struct Record24Storage {
    uint32_t begin;
    uint32_t end;
    uint32_t allocation_end;
    uint32_t RIFF_THISCALL growth_capacity(uint32_t required) const;
};
static_assert(sizeof(Record24Storage) == 12, "original vector triple");
#endif
