#include "impl.hpp"
namespace riff {
// VA 00579860..00579aa9. Caller 0053048b allocates 0xfc bytes,
// passes (12, "glass name", 0). No index validation or pointer ownership.
// Ordinary-return semantics only: original SEH states -1/0/1, handler
// 00908136, base destructor 0052c9f0 and member +f4 cleanup 00499d50
// remain Windows runtime dependencies. No invented exception behavior.
GlassShader::GlassShader(uint32_t index,const char* shaderName,uint32_t arg) {
    GlassServices s;
    s.base=reinterpret_cast<GlassShader* (RC_THISCALL *)(GlassShader*)>(0x5421b0);
    s.lookup=reinterpret_cast<uint32_t (RC_STDCALL *)(uint32_t,const char*)>(0x542340);
    s.common=reinterpret_cast<void (RC_THISCALL *)(GlassShader*)>(0x542230);
    s.manager=*reinterpret_cast<const uint32_t* const*>(0xbfcd04);
    construct(index,shaderName,arg,s);
}
GlassShader* RC_THISCALL GlassShader::construct(uint32_t index,const char* shaderName,
                                              uint32_t arg,const GlassServices& s) {
    s.base(this);
    vtable=0xa01940;
    name=shaderName; reserved5c=0; shaderIndex=index; unknownF0=0; memberF4=0;
    flagF8=0; argument=arg;
    // x86 address calculation wraps modulo 2^32. The manager entry starts
    // eight bytes into the table, and has four DWORDs per shader index.
    const uint32_t address=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(s.manager)) + index*16u;
    const uint32_t* entry=reinterpret_cast<const uint32_t*>(static_cast<uintptr_t>(address));
    for(unsigned i=0;i<16;++i)transform[i]=(i%5==0)?1.0f:0.0f;
    vertexShader=entry[2];pixelShader=entry[4];
    vertexConstants=entry[3];pixelConstants=entry[5];
    worldViewProjection=s.lookup(vertexConstants,"matWorldViewProj");
    worldMatrix=s.lookup(vertexConstants,"matWorld");
    worldInverse=s.lookup(vertexConstants,"matWorldInverse");
    cameraPos=s.lookup(vertexConstants,"cameraPos");
    inverseView=s.lookup(vertexConstants,"matInvView");
    lightDir=s.lookup(vertexConstants,"lightDir");
    lightAmbient=s.lookup(pixelConstants,"lightAmbient");
    lightDiffuse=s.lookup(pixelConstants,"lightDiffuse");
    lightSpecular=s.lookup(pixelConstants,"lightSpecular");
    reflectionStrength=s.lookup(pixelConstants,"s_reflectionStrength");
    glassColor=s.lookup(pixelConstants,"s_glassColor");
    reflectionColor=s.lookup(pixelConstants,"g_reflectionColor");
    illuminateColor=s.lookup(pixelConstants,"g_illuminateColor");
    cubeColor=s.lookup(pixelConstants,"s_cubeColor");
    s.common(this);
    return this;
}
}
