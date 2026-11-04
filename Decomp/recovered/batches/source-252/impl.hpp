#ifndef RIFF_CARGLASS_HPP
#define RIFF_CARGLASS_HPP
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
typedef uint32_t (RIFF_STDCALL *NamedParameter)(ShaderResource*,uint32_t,const char*);
struct ResourceVtable { uint32_t unused[9]; NamedParameter namedParameter; };
struct ShaderResource { ResourceVtable* vtable; };
struct ShaderManager {
    uint8_t unknown[0x8d8];
    uint32_t vertexProgram;
    ShaderResource* vertexParameters;
    uint32_t pixelProgram;
    ShaderResource* pixelParameters;
};
// External port binding; original manager pointer is stored at VA 0xbfcd04.
extern ShaderManager* shader_manager;
struct CarGlass {
    uint32_t vtable; // original vtable identity, not a native C++ vptr
    uint32_t vertexProgram,pixelProgram,unknown0c;
    ShaderResource* vertexParameters;
    ShaderResource* pixelParameters;
    uint32_t commonParameters[16]; // +18..54, accepted common helper
    uint8_t flag58,flag59,padding5a[2]; // names/meaning of flags unresolved
    uint32_t member5c; // initialized empty; ownership/type unresolved
    uint32_t worldViewProjection,inverseView,cameraPosition,diffuse,reflectiveness;
    float transform[4][4]; // +74..b3
    uint32_t unknownB4;
    RIFF_THIS CarGlass(uint8_t first,uint8_t second);
    CarGlass* RIFF_THIS construct(uint8_t first,uint8_t second);
    // Accepted dependencies, defined by the port or the test's oracle bindings.
    void RIFF_THIS initializeBase();
    void RIFF_THIS initializeCommonParameters();
};
static_assert(sizeof(CarGlass)==0xb8,"original i386 layout");
static_assert(offsetof(CarGlass,flag58)==0x58,"flags");
static_assert(offsetof(CarGlass,transform)==0x74,"matrix");
static_assert(offsetof(ShaderManager,vertexProgram)==0x8d8,"manager entry");
#endif
