#ifndef RIFF_HULL_SUPPORT_HPP
#define RIFF_HULL_SUPPORT_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
struct Vector4 { float x, y, z, w; };
// Partial btConvexHullShape layout. Unknown/base fields are deliberately opaque.
struct ConvexHull {
    uint8_t base[12];
    Vector4 localScaling;                 // +0x0c (unaligned vector)
    uint8_t unknown1[0x58-0x1c];
    int32_t capacity;                     // +0x58, not used here
    int32_t vertexCount;                  // +0x5c
    uint32_t unknown2;                    // +0x60
    Vector4* vertices;                    // +0x64, 16-byte stride
    void RIFF_THISCALL batchedSupportWithoutMargin(
        const Vector4* directions, Vector4* support, int32_t directionCount) const;
};
static_assert(offsetof(ConvexHull, vertexCount)==0x5c,"vertex count layout");
static_assert(offsetof(ConvexHull, vertices)==0x64,"vertex pointer layout");
}
#endif
