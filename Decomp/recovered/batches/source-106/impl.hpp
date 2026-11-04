#ifndef RIFF_VIEWPORT_HPP
#define RIFF_VIEWPORT_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct WindowOffsets {
    uint8_t unknown00[0x14];
    uint32_t x, y;
};
typedef void (*FitDimensions)(uint32_t* width, uint32_t* height);
// Bind this adapter to original 0x4A1C30 (ECX=width pointer, stack=height
// pointer) or its separately recovered port. This task does not recover it.
extern FitDimensions fitDimensions;
// Portable binding for the original singleton pointer at 0xBFCC28.
extern WindowOffsets* window;
struct Viewport {
    uint8_t unknown000[0x294];
    int32_t heightTenthMinusTwo; // Semantic name only; consumer purpose unresolved.
    uint8_t unknown298[0x48c-0x298];
    uint32_t requestedWidth, requestedHeight;
    uint32_t width, height, offsetX, offsetY;
    uint8_t unknown4a4[0x4b8-0x4a4];
    uint8_t fitEnabled;
#ifdef _MSC_VER
    void __thiscall setSize(uint32_t requestedW, uint32_t requestedH);
#else
    void __attribute__((thiscall)) setSize(uint32_t requestedW, uint32_t requestedH);
#endif
};
static_assert(offsetof(Viewport,fitEnabled)==0x4b8,"viewport layout");
static_assert(offsetof(Viewport,requestedWidth)==0x48c,"viewport layout");
static_assert(offsetof(Viewport,heightTenthMinusTwo)==0x294,"viewport layout");
}
#endif
