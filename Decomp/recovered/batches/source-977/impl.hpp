#ifndef RIFF_AUDIO_INDEX_HPP
#define RIFF_AUDIO_INDEX_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif

// Original x86 object layout; names describe use, not recovered debug names.
struct AudioIndex {
    uint32_t* entries;       // +0x00, opaque 32-bit index values
    uint32_t stride;         // +0x04
    uint32_t coveredUnits;   // +0x08, count * stride modulo 2^32
    uint32_t capacity;       // +0x0c
    uint32_t count;          // +0x10
    uint32_t growth;         // +0x14, used by caller, untouched here

    void RIFF_THISCALL compactEven();
};
#endif
