#ifndef RIFF_CONVEX_EDGE_HPP
#define RIFF_CONVEX_EDGE_HPP
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
// Partial original object layout; opaque bytes have no recovered meaning here.
struct ConvexHull {
    unsigned char opaque00[12];
    Vector4 scaling;                        // +0x0c
    unsigned char opaque1c[64];
    int32_t vertexCount;                    // +0x5c
    unsigned char opaque60[4];
    Vector4* vertices;                      // +0x64 on original i386
    void RIFF_THISCALL edgeWithoutMargin(int32_t edge, Vector4& a, Vector4& b);
};
static_assert(offsetof(ConvexHull, scaling)==0x0c, "scaling offset");
static_assert(offsetof(ConvexHull, vertexCount)==0x5c, "count offset");
#if UINTPTR_MAX == 0xffffffffu
static_assert(offsetof(ConvexHull, vertices)==0x64, "vertices offset");
#endif
}
#endif
