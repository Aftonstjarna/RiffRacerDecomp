#include "impl.hpp"
namespace riff {
// Game.exe VA 0x47d530, RVA 0x7d530, 37 bytes; sphere vtable
// 0x9f987c slot +0x3c. ECX is unused; result and direction are stack
// arguments, ret 8, EAX returns result. No sphere fields are accessed.
// The caller at 0x47d5bf loads this slot, pushes direction then a local
// result at 0x47d5c5/6, and reads 16 bytes through returned EAX.
// Every lane, including w, becomes +0. No normalization or radius lookup.
Vector4* RIFF_THISCALL Sphere::supportWithoutMargin(
    Vector4* result, const Vector4* /*direction*/) const {
    result->x = 0.0f;
    result->y = 0.0f;
    result->z = 0.0f;
    result->w = 0.0f;
    return result;
}
}
