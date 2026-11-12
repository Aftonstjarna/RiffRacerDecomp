#ifndef RIFF_BOX_SHAPE_HPP
#define RIFF_BOX_SHAPE_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Recovered prefix of the 0x34-byte allocation seen at 0x46cc10.
// Names describe observed values; original class/type names are unresolved.
struct BoxShape {
    uint32_t vtable_address;     // +00 original image identity, not a portable vtable
    uint32_t field04;
    uint32_t field08;
    float scale[3];              // +0c
    uint32_t field18;
    float scaled_dimensions[4];  // +1c, fourth lane is positive zero
    float margin;               // +2c
    uint32_t untouched30;
    BoxShape* RIFF_THISCALL construct(const float* dimensions);
};
static_assert(sizeof(BoxShape) == 0x34, "original allocation size");
#endif
