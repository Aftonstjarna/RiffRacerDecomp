#include "impl.hpp"
namespace riff {
// Game.exe 0x47d710, 205 bytes; sphere vtable 0x9f987c slot +4.
// Caller 0x460f33 passes a copied 64-byte transform then two vector outputs;
// 0x47db87 uses the same slot and merges the resulting bounds.
// Original +0x28 target 0x4391c0 multiplies shape floats +0x1c and +0x0c
// using x87. That dependency is intentionally left virtual, not recovered here.
void RIFF_THISCALL Sphere::aabb(const Transform* transform, Vector4* lower, Vector4* upper) {
    // Separate calls and float rounding are observable for changing overrides.
    const float zExtent = vtable->margin(this);
    const float yExtent = vtable->margin(this);
    const float xExtent = vtable->margin(this);
    Vector4 bound;
    bound.x = transform->rows[3].x - xExtent;
    bound.y = transform->rows[3].y - yExtent;
    bound.z = transform->rows[3].z - zExtent;
    bound.w = 0.0f;
    *lower = bound;
    // Do not cache translation: lower may alias transform->rows[3].
    bound.x = transform->rows[3].x + xExtent;
    bound.y = transform->rows[3].y + yExtent;
    bound.z = transform->rows[3].z + zExtent;
    bound.w = 0.0f;
    *upper = bound;
}
}
