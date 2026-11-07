#ifndef RIFF_PENDING_TARGETS_HPP
#define RIFF_PENDING_TARGETS_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_STDCALL __stdcall
#define RIFF_THISCALL __thiscall
#else
#define RIFF_STDCALL __attribute__((stdcall))
#define RIFF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
struct ComResource;
struct ComVtable {
    // Only Release is used here; the preceding COM entries remain opaque.
    void (RIFF_STDCALL *query_interface)();
    void (RIFF_STDCALL *add_ref)();
    uint32_t (RIFF_STDCALL *release)(ComResource*);
};
struct ComResource { const ComVtable* vtable; };
struct Viewport {
    uint32_t x, y, width, height;
    float min_depth, max_depth;
};
// Prefix of the larger device object, not a complete device class.
struct DevicePendingTargets {
    uint8_t flags[4];                 // +00: left untouched
    ComResource* color_texture[2];    // +04, +08
    ComResource* color_surface[2];    // +0c, +10
    ComResource* depth_surface;       // +14
    ComResource* readback_surface;    // +18
    Viewport viewport;               // +1c..+33
    void RIFF_THISCALL cleanup();
};
static_assert(sizeof(void*) != 4 || offsetof(DevicePendingTargets, viewport) == 0x1c, "i386 layout");
static_assert(sizeof(Viewport) == 24, "viewport layout");
}
#endif
