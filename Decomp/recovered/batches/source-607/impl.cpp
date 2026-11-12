#include "impl.hpp"
// Bytewise access preserves original aliasing even when input points at integer
// header words. It also permits the unaligned loads supported by original MOVSS.
static void read_component(const void* input, unsigned offset, float& value) {
    unsigned char* out = reinterpret_cast<unsigned char*>(&value);
    const unsigned char* in = static_cast<const unsigned char*>(input) + offset;
    for (unsigned i = 0; i < 4; ++i) out[i] = in[i];
}
// Original 0x438ab0..0x438b35: ECX=this, one stack pointer argument,
// callee pops 4 bytes, EAX=this. No calls, allocation, SEH or validation.
BoxShape* RIFF_THISCALL BoxShape::construct(const float* dimensions) {
    field08 = 0;
    scale[0] = 1.0f;
    scale[1] = 1.0f;
    scale[2] = 1.0f;
    field18 = 0;
    margin = 0.04f;
    vtable_address = 0x009f98d0u;
    field04 = 0;
    // Keep the actual scalar multiplies: DAZ, denormals and signaling NaNs
    // make a copy different from multiplication by 1. Stage all reads before
    // writing the destination, as the original allows overlapping input.
    const volatile float* factors = scale;
    float x, y, z;
    read_component(dimensions, 0, x);
    x *= factors[0];
    read_component(dimensions, 4, y);
    y *= factors[1];
    read_component(dimensions, 8, z);
    z *= factors[2];
    scaled_dimensions[0] = x;
    scaled_dimensions[1] = y;
    scaled_dimensions[2] = z;
    scaled_dimensions[3] = 0.0f;
    return this;
}
