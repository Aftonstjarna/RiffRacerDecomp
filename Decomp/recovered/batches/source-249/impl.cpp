#include "impl.hpp"
namespace riff {
// VA 00576c20..00576ce0; ECX=this, one stack DWORD, RET 4, EAX=this.
// Callers 00532e48..00532f92 allocate 0x70 bytes and pass indices 119..125.
// The three accepted helpers remain external dependencies, not reimplementations.
// Normal-return behavior only: the original registers SEH handler 00905468,
// marks the base constructed, and restores FS:[0]. Windows unwind is unresolved.
ShadowDrawShader::ShadowDrawShader(uint32_t index) {
    typedef ShadowDrawShader* (RIFF_THISCALL *Base)(ShadowDrawShader*);
    typedef uint32_t (RIFF_STDCALL *Lookup)(uint32_t,const char*);
    typedef void (RIFF_THISCALL *Common)(ShadowDrawShader*);
    const Base base=reinterpret_cast<Base>(0x5421b0);
    const Lookup lookup=reinterpret_cast<Lookup>(0x542340);
    const Common common=reinterpret_cast<Common>(0x542230);
    base(this);
    const uint32_t manager=*reinterpret_cast<const uint32_t*>(0xbfcd04);
    vtable=0xa013d8;
    unknown64=0;
    unknown68=0;
    shaderIndex=index;
    // x86 effective-address arithmetic wraps modulo 2^32. There are no
    // bounds/null checks in the original; invalid manager entries still fault.
    const uint32_t address=manager+index*16u;
    const uint32_t* entry=reinterpret_cast<const uint32_t*>(static_cast<uintptr_t>(address));
    vertexShader=entry[2];
    pixelShader=entry[4];
    vertexConstants=entry[3];
    pixelConstants=entry[5];
    worldViewProjection=lookup(vertexConstants,"matWorldViewProj");
    // Reload fields after each external call: callbacks can alter the object.
    vertexTexelOffset=lookup(vertexConstants,"texelOffset");
    pixelTexelOffset=lookup(pixelConstants,"texelOffset");
    common(this);
}
}
