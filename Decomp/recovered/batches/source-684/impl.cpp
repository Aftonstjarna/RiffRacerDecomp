#include "impl.hpp"
// Game.exe 0x47d560..0x47d596, sphere vtable 0x9f987c slot +0x40.
// ECX=this is unused; ret 12 removes directions, outputs, signed count.
// The loop stores zero dwords at offsets 0,4,8,12 with stride 16.
// Virtual batch callers (e.g. 0x47ba46, 0x47bfe6, 0x47ce9e) pass
// six direction vectors and six output vectors, then read output xyz.
// No radius/margin lookup, direction read, floating arithmetic, or return value.
void RIFF_THISCALL riff::Sphere::batchedSupportWithoutMargin(
    const Vector4* /*directions*/, Vector4* outputs, int32_t count) const {
    for (int32_t i = 0; i < count; ++i) {
        outputs[i].x = 0.0f;
        outputs[i].y = 0.0f;
        outputs[i].z = 0.0f;
        outputs[i].w = 0.0f;
    }
}
