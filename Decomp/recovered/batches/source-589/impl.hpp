#ifndef RIFF_PREPARE_HPP
#define RIFF_PREPARE_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#define RIFF_STDCALL __stdcall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#define RIFF_STDCALL __attribute__((stdcall))
#endif
namespace riff {
struct Object { void** vtable; };
struct Viewport { uint32_t x,y,width,height; float minimum,maximum; };
struct Device {
    uint8_t pending,bound,mode,bound_mode;
    Object* resources[6]; // +04/+08 textures; +0c/+10 color; +14 depth; +18 readback
    Viewport viewport;
    uint8_t unknown34[0x78-0x34];
    Object* graphics;
    uint8_t unknown7c[0xd8-0x7c];
    uint32_t requested_width;
    uint8_t unknowndc[0x1e0-0xdc];
    uint32_t depth_format;
    uint8_t unknown1e4[0x1f8-0x1e4];
    uint32_t color_format;
    bool RIFF_THISCALL prepare_pending();
    void RIFF_THISCALL cleanup_pending(); // accepted dependency, 004a4ea0
};
static_assert(sizeof(void*)!=4 || offsetof(Device,color_format)==0x1f8,"layout");
static_assert(sizeof(void*)!=4 || offsetof(Device,graphics)==0x78,"layout");
}
#endif
