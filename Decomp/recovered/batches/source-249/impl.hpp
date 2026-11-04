#ifndef RIFF_SHADOWDRAW_HPP
#define RIFF_SHADOWDRAW_HPP
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
// Original i386 layout, not a native 64-bit graphics interface.
struct ShadowDrawShader {
    uint32_t vtable;                          // 00: wsShaderShadowDraw
    uint32_t vertexShader, pixelShader;       // 04,08: borrowed manager objects
    uint32_t reserved0c;                      // 0c: base initializes to zero
    uint32_t vertexConstants,pixelConstants;  // 10,14: borrowed constant tables
    uint32_t commonHandles[16];               // 18..54: external common helper
    uint32_t worldViewProjection;             // 58
    uint32_t vertexTexelOffset,pixelTexelOffset; // 5c,60
    uint32_t unknown64,unknown68,shaderIndex;  // 64,68,6c
    RIFF_THISCALL ShadowDrawShader(uint32_t index);
};
static_assert(sizeof(ShadowDrawShader)==0x70,"original object size");
static_assert(offsetof(ShadowDrawShader,worldViewProjection)==0x58,"handle offset");
static_assert(offsetof(ShadowDrawShader,shaderIndex)==0x6c,"index offset");
}
#endif
