#ifndef RIFF_CARLIGHTS_HPP
#define RIFF_CARLIGHTS_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_THIS __thiscall
#define RIFF_STDCALL __stdcall
#else
#define RIFF_THIS __attribute__((thiscall))
#define RIFF_STDCALL __attribute__((stdcall))
#endif
struct ShaderResource;
typedef uint32_t (RIFF_STDCALL *NamedParameter)(ShaderResource*, uint32_t, const char*);
struct ResourceVtable { uint32_t unused[9]; NamedParameter namedParameter; };
struct ShaderResource { ResourceVtable* vtable; };
struct ShaderManager {
    uint8_t unknown[0x8e8];
    uint32_t vertexProgram;
    ShaderResource* vertexParameters;
    uint32_t pixelProgram;
    ShaderResource* pixelParameters;
};
extern ShaderManager* shader_manager;
struct CarLights {
    uint32_t vtable;                  // +00 original table identity, not a host C++ vptr
    uint32_t vertexProgram, pixelProgram;
    uint32_t unknown0c;
    ShaderResource* vertexParameters; // +10
    ShaderResource* pixelParameters;  // +14
    uint32_t commonParameters[16];    // +18..54, populated by common helper
    uint32_t worldViewProjection;     // +58
    uint32_t lightColour;             // +5c
    float transform[4][4];            // +60..9f identity
    uint32_t variant;                 // +a0; copied without range checking
    CarLights* RIFF_THIS construct(uint32_t selectedVariant);
    // Port bindings to accepted original helpers at 0x5421b0 / 0x542230.
    // These remain dependencies, not recovered implementations in this task.
    void RIFF_THIS initializeBase();
    void RIFF_THIS initializeCommonParameters();
};
static_assert(sizeof(CarLights)==0xa4, "original x86 layout");
static_assert(offsetof(CarLights, transform)==0x60, "transform offset");
#endif
