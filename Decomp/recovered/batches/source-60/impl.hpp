#ifndef RIFF_SHADER_RELEASE_HPP
#define RIFF_SHADER_RELEASE_HPP
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
struct Callback;
struct CallbackVtable {
    void* (RIFF_THISCALL *destroy)(Callback*, unsigned);
    void* unknown1;
    void* unknown2;
    void* unknown3;
    void (RIFF_THISCALL *cleanup)(Callback*);
};
struct Callback { CallbackVtable* vtable; };
struct Resource;
struct ResourceVtable {
    void* unknown0;
    void* unknown1;
    uint32_t (RIFF_STDCALL *release)(Resource*);
};
struct Resource { ResourceVtable* vtable; };
struct ShaderRecord {
    Resource* vertexShader;
    Resource* vertexConstants;
    Resource* pixelShader;
    Resource* pixelConstants;
};
struct ShaderManager {
    uint32_t unknownHeader[2];
    ShaderRecord shaders[225];
    Callback** callbacks;
    Callback* bindings[6][280];
    void release();
};
static_assert(sizeof(void*) == 4, "Original layout requires a 32-bit target");
static_assert(offsetof(ShaderManager, callbacks) == 0xe18, "callback field");
static_assert(offsetof(ShaderManager, bindings) == 0xe1c, "binding tables");
}
#endif
