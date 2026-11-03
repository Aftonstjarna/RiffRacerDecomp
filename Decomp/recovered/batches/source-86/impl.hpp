#ifndef RIFF_SHADER_PAIR_HPP
#define RIFF_SHADER_PAIR_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_STDCALL __stdcall
#define RIFF_THISCALL __thiscall
#else
#define RIFF_STDCALL __attribute__((stdcall))
#define RIFF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
struct Interface { void** vtable; };
typedef int32_t (RIFF_STDCALL *CreateShader)(Interface*, const uint32_t*, Interface**);
typedef int32_t (RIFF_STDCALL *GetConstants)(const uint32_t*, Interface**);
typedef uint32_t (RIFF_STDCALL *Release)(Interface*);
struct DeviceOwner { unsigned char unknown[0x78]; Interface* device; };
struct ShaderPair {
    Interface* vertex;
    Interface* vertexConstants;
    Interface* pixel;
    Interface* pixelConstants;
    bool RIFF_THISCALL create(const uint32_t* vertexCode, const uint32_t* pixelCode);
    // Dependency adapter for ports. Owner and import slots remain live across calls.
    bool createUsing(const uint32_t*, const uint32_t*, DeviceOwner* volatile*, GetConstants volatile*);
};
}
#endif
