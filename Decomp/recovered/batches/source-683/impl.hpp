#ifndef RIFF_SPHERE_SUPPORT_HPP
#define RIFF_SPHERE_SUPPORT_HPP
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
static_assert(sizeof(Vector4) == 16, "Original vector storage");
// Only the recovered operation is modeled; sphere fields/layout remain opaque.
class Sphere {
public:
    Vector4* RIFF_THISCALL supportWithoutMargin(Vector4* result,
                                               const Vector4* direction) const;
};
}
#endif
