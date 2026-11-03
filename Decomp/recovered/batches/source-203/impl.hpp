#ifndef RIFF_NORMALMAPPED_HPP
#define RIFF_NORMALMAPPED_HPP
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
struct NormalMappedShader;
struct NormalMappedServices {
 NormalMappedShader* (RC_THISCALL *base)(NormalMappedShader*);
 uint32_t (RC_STDCALL *lookup)(uint32_t,const char*);
 void (RC_THISCALL *common)(NormalMappedShader*);
 const uint32_t* manager;
};
// Explicit original i386 layout. GPU pointers/handles need adaptation on 64-bit ports.
struct NormalMappedShader {
 uint32_t vtable,vertexShader,pixelShader,argument,vertexConstants,pixelConstants;
 uint32_t commonHandles[16];
 const char* name; // borrowed
 uint32_t worldViewProjection,worldMatrix,worldInverse,cameraPos;
 uint32_t lightDir,lightDir2,lightDir3,lightAmbient,lightDiffuse,lightSpecular;
 float transform[16];
 uint32_t unknownC4[12]; // c4..f0, untouched
 uint32_t lightPoints,lightFalloffDistance,attenuationFactor,dirtScale,dirtColor,screenSpaceUVAdjust;
 uint32_t unknown10c;
 uint8_t isIndex53,isIndex5b,padding[2];
 RC_THISCALL NormalMappedShader(uint32_t index,const char* shaderName,uint32_t arg);
 NormalMappedShader* RC_THISCALL construct(uint32_t index,const char* shaderName,uint32_t arg,const NormalMappedServices& services);
};
static_assert(sizeof(NormalMappedShader)==0x114,"original allocation size");
static_assert(offsetof(NormalMappedShader,transform)==0x84,"matrix");
static_assert(offsetof(NormalMappedShader,lightPoints)==0xf4,"extended handles");
static_assert(offsetof(NormalMappedShader,isIndex53)==0x110,"flags");
}
#endif
