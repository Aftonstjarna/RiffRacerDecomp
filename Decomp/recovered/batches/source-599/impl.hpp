#ifndef RIFF_BOX_VERTEX_HPP
#define RIFF_BOX_VERTEX_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
struct Vector4 { float x, y, z, w; };
// Partial layout only: no claim about the identities of the preceding fields.
struct BoxShape {
    uint8_t unresolved_prefix[0x1c];
    Vector4 half_extents_without_margin;
    void RIFF_THISCALL vertex_without_margin(int32_t index, Vector4* output) const;
};
static_assert(offsetof(BoxShape, half_extents_without_margin) == 0x1c, "original field offset");
static_assert(sizeof(Vector4) == 16, "original vector size");
}
#endif
