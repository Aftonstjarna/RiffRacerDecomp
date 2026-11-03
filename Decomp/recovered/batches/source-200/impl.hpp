#ifndef RIFF_GLASS_HPP
#define RIFF_GLASS_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RC_THISCALL __thiscall
#define RC_STDCALL __stdcall
#else
#define RC_THISCALL __attribute__((thiscall))
#define RC_STDCALL __attribute__((stdcall))
#endif
namespace riff {
struct GlassShader;
// External services are deliberately outside this recovered constructor's scope.
// This is the original 32-bit object layout; a 64-bit port must adapt handles
// and pointers rather than treating this structure as a native GPU object.
struct GlassServices {
    GlassShader* (RC_THISCALL *base)(GlassShader*);
    uint32_t (RC_STDCALL *lookup)(uint32_t,const char*);
    void (RC_THISCALL *common)(GlassShader*);
    const uint32_t* manager;
};
struct GlassShader {
    uint32_t vtable;                       // 00: original wsShaderGlass vtable
    uint32_t vertexShader, pixelShader;    // 04,08
    uint32_t argument;                     // 0c: third constructor argument
    uint32_t vertexConstants,pixelConstants; // 10,14
    uint32_t commonHandles[16];            // 18..54, populated by external helper
    const char* name;                      // 58: borrowed second argument
    uint32_t reserved5c;
    uint32_t worldViewProjection,worldMatrix,worldInverse,cameraPos; // 60..6c
    uint32_t lightDir,lightAmbient,lightDiffuse,lightSpecular;  // 70..7c
    uint32_t unknown80;
    float transform[16];                   // 84..c0: identity
    uint32_t inverseView;              // c4
    uint32_t reflectionStrength,glassColor,cubeColor; // c8,cc,d0
    uint32_t reflectionColor,illuminateColor;   // d4,d8: looked up before cubeColor
    uint32_t unknownDc[4];                 // dc..e8: untouched
    uint32_t shaderIndex,unknownF0,memberF4; // ec,f0,f4
    uint8_t flagF8,paddingF9[3];            // f8 cleared; tail padding untouched

    RC_THISCALL GlassShader(uint32_t index,const char* shaderName,uint32_t arg);
    GlassShader* RC_THISCALL construct(uint32_t index,const char* shaderName,uint32_t arg,
                                     const GlassServices& services);
};
static_assert(sizeof(GlassShader)==0xfc,"i386 object layout");
static_assert(offsetof(GlassShader,transform)==0x84,"matrix offset");
static_assert(offsetof(GlassShader,shaderIndex)==0xec,"index offset");
}
#endif
