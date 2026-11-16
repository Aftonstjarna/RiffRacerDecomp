#ifndef RIFF_SIMPLEX_RESULT_HPP
#define RIFF_SIMPLEX_RESULT_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif

// Observed result subobject at simplex+0x13c. Names are descriptive rather
// than recovered debug symbols. Only offsets through 0x24 are established.
struct SimplexResult {
    uint8_t preservedPrefix[0x10];
    uint16_t flags;
    uint8_t preserved12[2];
    float weights[4];
    uint8_t status;
    // Natural trailing alignment padding is not touched by reset.
    void RIFF_THISCALL reset();
};
static_assert(offsetof(SimplexResult, flags) == 0x10, "flags offset");
static_assert(offsetof(SimplexResult, weights) == 0x14, "weights offset");
static_assert(offsetof(SimplexResult, status) == 0x24, "status offset");
static_assert(sizeof(SimplexResult) == 0x28, "modeled storage size");
#endif
