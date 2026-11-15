#ifndef RIFF_SPHERE_AABB_HPP
#define RIFF_SPHERE_AABB_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
struct Vector4 { float x, y, z, w; };
struct Transform { Vector4 rows[4]; };
struct Sphere;
typedef float (RIFF_THISCALL *MarginFunction)(Sphere*);
// Only slot +0x28 is used here. Other slots are deliberately uninterpreted.
struct SphereVtable { void* unused[10]; MarginFunction margin; };
struct Sphere {
    SphereVtable* vtable;
    uint32_t opaque[12]; // Original allocation is 0x34 bytes, including vptr.
    void RIFF_THISCALL aabb(const Transform* transform, Vector4* lower, Vector4* upper);
};
}
#endif
