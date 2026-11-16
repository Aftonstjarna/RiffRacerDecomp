#ifndef RIFF_PHASE_HPP
#define RIFF_PHASE_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_FASTCALL __fastcall
#elif defined(__i386__)
#define RIFF_FASTCALL __attribute__((fastcall))
#else
#define RIFF_FASTCALL
#endif
// Partial audio-state layout. Unknown bytes are retained, not interpreted.
struct AudioResampleState {
    unsigned char unknown0[0x4ba0];
    uint32_t phaseFactor; // +0x4ba0: interpretation beyond multiplication unresolved
    unsigned char unknown1[0x4cec - 0x4ba4];
    uint32_t phaseScale; // +0x4cec
    int32_t RIFF_FASTCALL phaseAtCount(int32_t count) const;
};
static_assert(offsetof(AudioResampleState, phaseFactor) == 0x4ba0, "layout");
static_assert(offsetof(AudioResampleState, phaseScale) == 0x4cec, "layout");
#endif
