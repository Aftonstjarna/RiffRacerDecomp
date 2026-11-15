#ifndef RIFF_CONVEX_HULL_HPP
#define RIFF_CONVEX_HULL_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
struct HullVector { float x, y, z, w; };
// Partial original 32-bit object layout. Unknown fields remain opaque.
// Not a recovered class hierarchy: the original vtable is preserved as data.
struct ConvexHull {
    uint8_t unknown00[12];
    HullVector localScaling; // XYZ at +0x0c, +0x10, +0x14
    uint8_t unknown1c[72];
    HullVector* vertices; // +0x64; array stride 16
    void RIFF_THISCALL vertexWithoutMargin(int32_t index, HullVector& output) const;
};
static_assert(sizeof(HullVector) == 16, "vertex stride");
static_assert(offsetof(ConvexHull, vertices) == 0x64, "original vertex pointer");
#endif
