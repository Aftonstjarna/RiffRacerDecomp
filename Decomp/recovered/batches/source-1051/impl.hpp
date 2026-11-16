#ifndef RECORD12_IMPL_HPP
#define RECORD12_IMPL_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RECORD12_THISCALL __thiscall
#elif defined(__i386__)
#define RECORD12_THISCALL __attribute__((thiscall))
#else
#define RECORD12_THISCALL
#endif
// Original 32-bit vector header, addresses retained as words for portable
// inspection. No pointed-to records are read by this capacity calculation.
struct Record12Vector {
    uint32_t begin;
    uint32_t end;
    uint32_t capacity_end;
    uint32_t RECORD12_THISCALL capacity_growth(uint32_t minimum) const;
};
#endif
