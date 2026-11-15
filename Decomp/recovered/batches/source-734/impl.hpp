#ifndef RIFF_RECORD40_HPP
#define RIFF_RECORD40_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// VA 0x434320, 70 bytes. Opaque bit-preserving layout; no ownership or vptr.
// Caller 0x432d69 selects begin + index*40 into a stack destination.
// It subsequently reads words 0..8 as three float triples. Their semantic
// names and word 9's type are not established by this bounded recovery.
struct Record40 {
    uint32_t words[10];
    Record40& RIFF_THISCALL operator=(const Record40& source);
};
static_assert(sizeof(Record40) == 40, "original record size");
#endif
