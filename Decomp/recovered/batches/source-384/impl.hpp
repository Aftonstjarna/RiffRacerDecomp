#ifndef RIFF_VECTOR3_REFS_HPP
#define RIFF_VECTOR3_REFS_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Constructor-shaped entry at Game.exe 0x426f00 (39 bytes).
// Names describe the observed vector layout; original source names are unknown.
struct Vector3 {
    float x, y, z, fourth;
    // Exposes the original constructor's EAX=this result for portable callers.
    Vector3* RIFF_THISCALL construct_refs(const float& a, const float& b, const float& c);
};
static_assert(sizeof(float) == 4 && sizeof(Vector3) == 16, "original layout");
#endif
