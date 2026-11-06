#ifndef RIFF_PAIR_COPY_HPP
#define RIFF_PAIR_COPY_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
// Partial owner layout only; no names for the unknown surrounding fields.
struct PairCopyOwner {
    unsigned char unknown00[0x44];
    unsigned char* nested;
    bool RIFF_THISCALL copyRecordPair(void* first, void* second);
};
#endif
