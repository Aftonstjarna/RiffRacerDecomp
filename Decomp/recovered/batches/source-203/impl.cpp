#include "impl.hpp"
namespace riff {
// VA 5789c0..578c1a; thiscall, three stack DWORDs, RET 12, EAX=this.
// Caller 531d80 allocates 114h bytes; 531d9e passes (51h,9ff3ach,0).
// Only ordinary returns recovered. Windows SEH handler 905468, metadata
// b7d1e0 and exception cleanup are unresolved; no invented unwind behavior.
NormalMappedShader::NormalMappedShader(uint32_t index,const char* shaderName,uint32_t arg) {
 NormalMappedServices s;
 s.base=reinterpret_cast<NormalMappedShader* (RC_THISCALL *)(NormalMappedShader*)>(0x5421b0);
 s.lookup=reinterpret_cast<uint32_t (RC_STDCALL *)(uint32_t,const char*)>(0x542340);
 s.common=reinterpret_cast<void (RC_THISCALL *)(NormalMappedShader*)>(0x542230);
 // Read manager after base construction, as the original does.
 s.manager=0;
 construct(index,shaderName,arg,s);
}
NormalMappedShader* RC_THISCALL NormalMappedShader::construct(uint32_t index,const char* shaderName,uint32_t arg,const NormalMappedServices& s) {
 s.base(this);
 const uint32_t* manager=s.manager?s.manager:*reinterpret_cast<const uint32_t* const*>(0xbfcd04);
 name=shaderName;vtable=0xa01808;argument=arg;
 // No bounds checks: original x86 effective-address arithmetic wraps at 32 bits.
 const uint32_t address=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(manager))+index*16u;
 const uint32_t* entry=reinterpret_cast<const uint32_t*>(static_cast<uintptr_t>(address));
 const uint32_t vertex=entry[2];
 for(unsigned i=0;i<16;++i)transform[i]=(i%5==0)?1.0f:0.0f;
 vertexShader=vertex;pixelShader=entry[4];vertexConstants=entry[3];pixelConstants=entry[5];
 // Fields are reread at each call: callbacks may replace the constant tables.
 worldViewProjection=s.lookup(vertexConstants,"matWorldViewProj");
 worldMatrix=s.lookup(vertexConstants,"matWorld");
 worldInverse=s.lookup(vertexConstants,"matWorldInverse");
 cameraPos=s.lookup(vertexConstants,"cameraPos");
 lightDir=s.lookup(vertexConstants,"lightDir");
 lightDir2=s.lookup(vertexConstants,"lightDir2");
 lightDir3=s.lookup(vertexConstants,"lightDir3");
 lightAmbient=s.lookup(pixelConstants,"lightAmbient");
 lightDiffuse=s.lookup(pixelConstants,"lightDiffuse");
 lightSpecular=s.lookup(pixelConstants,"lightSpecular");
 lightPoints=s.lookup(vertexConstants,"lightPoints");
 lightFalloffDistance=s.lookup(pixelConstants,"g_lightFalloffDistance");
 attenuationFactor=s.lookup(pixelConstants,"g_attenuationFactor");
 dirtScale=s.lookup(pixelConstants,"g_dirtScale");
 dirtColor=s.lookup(pixelConstants,"g_dirtColor");
 screenSpaceUVAdjust=s.lookup(pixelConstants,"g_screenSpaceUVAdjust");
 isIndex53=index==0x53;isIndex5b=index==0x5b;
 s.common(this);return this;
}
}
