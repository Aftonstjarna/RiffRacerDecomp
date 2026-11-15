#ifndef RIFF_OBJECT_FLAGS_HPP
#define RIFF_OBJECT_FLAGS_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_FASTCALL __attribute__((fastcall))
#endif
// Partial layout only: names describe observed use, not recovered class names.
struct ObjectFlags {
    uint8_t unknown00[0x4c];
    uint32_t channel_mask;
    uint8_t unknown50[0x124];
    uint8_t flags;
    bool RIFF_FASTCALL channel_enabled(uint32_t channel) const;
};
static_assert(offsetof(ObjectFlags, channel_mask) == 0x4c, "mask offset");
static_assert(offsetof(ObjectFlags, flags) == 0x174, "flags offset");
#endif
