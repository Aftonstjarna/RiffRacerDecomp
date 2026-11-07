#ifndef RIFF_RESOURCE_INDEX_HPP
#define RIFF_RESOURCE_INDEX_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
// Partial 32-bit original object view. Addresses are original-width addresses,
// not owning pointers. Unidentified fields retain their offsets and contents.
struct ResourceIndex {
    uint32_t unknown00[13];
    uint32_t entriesBegin;       // +0x34
    uint32_t entriesEnd;         // +0x38
    uint32_t unknown3c;
    uint32_t counters;           // +0x40, parallel array of uint32_t
    uint32_t RIFF_THISCALL acquire(uint32_t index);
};
static_assert(offsetof(ResourceIndex, entriesBegin) == 0x34, "layout");
static_assert(offsetof(ResourceIndex, counters) == 0x40, "layout");
#endif
