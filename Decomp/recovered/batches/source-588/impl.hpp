#ifndef RIFF_PENDING_HPP
#define RIFF_PENDING_HPP
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
struct Object { void** vtable; };
struct Viewport { uint32_t x,y,width,height; float minimum,maximum; };
struct Device {
    uint8_t pending, bound, mode, bound_mode;
    Object* resources[6]; // +04 textures, +0c color surfaces, +14 depth, +18 auxiliary
    Viewport viewport; // +1c
    uint8_t unknown34[0x78-0x34];
    Object* graphics; // +78, IDirect3DDevice9-style stdcall vtable
    uint8_t unknown7c[0x450-0x7c];
    uint32_t color_index; // +450, unchecked by original
    // External recovered-reference dependencies: 004a4d80 and 004a4ea0.
    bool RIFF_THISCALL prepare_pending();
    void RIFF_THISCALL cleanup_pending();
    bool RIFF_THISCALL bind_pending(); // original 004a4f30..004a4faa
};
static_assert(sizeof(void*) != 4 || offsetof(Device,graphics)==0x78,"graphics offset");
static_assert(sizeof(void*) != 4 || offsetof(Device,color_index)==0x450,"index offset");
}
#endif
