#ifndef RIFF_TRANSFORM64_HPP
#define RIFF_TRANSFORM64_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Raw transform storage: no float interpretation is needed by this routine.
struct Transform64 {
    unsigned char bytes[64];
    void RIFF_THISCALL serialize_copy(void* destination) const;
};
static_assert(sizeof(Transform64) == 64, "transform extent");
#endif
