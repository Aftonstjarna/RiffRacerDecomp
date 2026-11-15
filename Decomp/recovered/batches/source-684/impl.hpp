#ifndef RIFF_SPHERE_BATCH_HPP
#define RIFF_SPHERE_BATCH_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
struct Vector4 { float x, y, z, w; };
static_assert(sizeof(Vector4) == 16, "Original vector stride");
// Only this operation is modeled. No sphere fields are accessed or inferred.
class Sphere {
public:
    void RIFF_THISCALL batchedSupportWithoutMargin(const Vector4* directions,
                                                  Vector4* outputs,
                                                  int32_t count) const;
};
}
#endif
