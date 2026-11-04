#include "impl.hpp"
#include <stddef.h>
using namespace riff;
extern "C" void __attribute__((thiscall)) original_shader_common_parameters(Shader*);
extern "C" ParameterHandle __attribute__((stdcall)) original_shader_parameter_lookup(ConstantTable*,const char*);
extern "C" void test_write(const char*,unsigned);
extern "C" void* memset(void* d,int c,unsigned n) { unsigned char* p=(unsigned char*)d; for(unsigned i=0;i<n;++i)p[i]=(unsigned char)c; return d; }
extern "C" void* memcpy(void* d,const void* s,unsigned n) { for(unsigned i=0;i<n;++i)((char*)d)[i]=((const char*)s)[i]; return d; }
namespace riff {
ParameterHandle RIFF_STDCALL lookupParameter(ConstantTable* t,const char* n) {
    return original_shader_parameter_lookup(t,n);
}
}
// Test-only original string data, transcribed from Game.exe .rdata.
// For complete successful-lookup differential tests link .oracle_names at
// 0x9fff74. This is data, never an instruction blob or oracle replacement.
struct Names {
    char fogColour[12],fogParams[12],alpha[12],fogHeight[20],reposition[20];
    char shadowPos[16],specular[16],shadow[12],mask[12],power[16],scale[16];
    char diffuse[16],ambient[16],morph[16],skin[16];
};
const Names oracle_names __attribute__((section(".oracle_names"),aligned(1),used)) = {
 "gFogColour","gFogParams","alphaValue","gFogHeightParams","g_repositionParams",
 "shadowMapPos","g_specularColor","shadowColor","maskColor","g_specularPower",
 "g_specularScale","g_diffuseColor","g_ambientColor","g_morphAmounts","skinMatrixArray"
};
static const char* const names[16]={"g_repositionParams","g_repositionParams","gFogParams","gFogColour",
 "gFogHeightParams","alphaValue","g_specularScale","g_specularPower","g_ambientColor",
 "g_diffuseColor","g_specularColor","shadowMapPos","maskColor","shadowColor","skinMatrixArray","g_morphAmounts"};
static const unsigned offsets[16]={0x18,0x1c,0x20,0x24,0x28,0x30,0x34,0x38,0x3c,0x40,0x44,0x2c,0x48,0x4c,0x50,0x54};
struct Description { const char* creator; uint32_t version,count; };
struct Parameter { const char* name; uint32_t rest[11]; };
struct Vtable {
    void* unused[5];
    int32_t (RIFF_STDCALL *describe)(ConstantTable*,Description*);
    int32_t (RIFF_STDCALL *parameter)(ConstantTable*,ParameterHandle,Parameter*,uint32_t*);
    void* unused7;
    ParameterHandle (RIFF_STDCALL *constant)(ConstantTable*,ParameterHandle,uint32_t);
};
namespace riff { struct ConstantTable { const Vtable* vtable; unsigned id; }; }
static ConstantTable tables[2];
static char handles[2][16];
struct Event { unsigned kind,id,index,count; Shader snapshot; };
static Event log1[2048],log2[2048];
static Event* events;
static unsigned eventCount,errors,descCalls,mutation;
static uint32_t missing;
static int32_t status;
static unsigned constants;
static Shader* active;
static bool equal(const void* a,const void* b,unsigned n) {
 for(unsigned i=0;i<n;++i) {
  if(((const char*)a)[i]!=((const char*)b)[i])return false;
 }
 return true;
}
static void record(unsigned kind,ConstantTable* t,unsigned index,unsigned count) {
 if(eventCount>=2048){++errors;return;}
 Event& e=events[eventCount++]; e.kind=kind;e.id=t->id;e.index=index;e.count=count;e.snapshot=*active;
}
static int32_t RIFF_STDCALL describe(ConstantTable* t,Description* d) {
 record(1,t,0,0); d->creator=0;d->version=0;d->count=constants;
 ++descCalls;
 // Reentrant table edits must be observed by subsequent lookups, even when
 // the current lookup fails. No extra scope is being recovered here.
 if(mutation && descCalls==3) { active->pixelConstants=mutation==1?&tables[0]:0; active->vertexConstants=&tables[1]; }
 return status;
}
static ParameterHandle RIFF_STDCALL constant(ConstantTable* t,ParameterHandle parent,uint32_t i) {
 record(2,t,i,0); if(parent || i>=16){++errors;return 0;}
 return (missing&(1u<<i))?0:&handles[t->id][i];
}
static int32_t RIFF_STDCALL parameter(ConstantTable* t,ParameterHandle h,Parameter* d,uint32_t* count) {
 unsigned i=0;while(i<16 && h!=&handles[t->id][i])++i;
 record(3,t,i,*count);if(i==16 || *count!=1){++errors;return -1;}
 d->name=names[i];*count=7;return -1; // Original deliberately ignores this status.
}
static const Vtable vtable={{0,0,0,0,0},describe,parameter,0,constant};
struct Guarded { uint32_t before[4]; Shader shader; uint32_t after[8]; };
static void reset(Shader* a,Event* log) { active=a;events=log;eventCount=0;descCalls=0;errors=0; }
static int run(unsigned nulls,int32_t st,unsigned count,uint32_t mask,unsigned mutate) {
 status=st;constants=count;missing=mask;mutation=mutate;
 Guarded a;memset(&a,0xa7,sizeof(a));
 a.shader.vertexConstants=(nulls&1)?0:&tables[0];a.shader.pixelConstants=(nulls&2)?0:&tables[1];
 Guarded b=a,initial=a;
 reset(&a.shader,log1);original_shader_common_parameters(&a.shader);
 unsigned n=eventCount,originalErrors=errors;
 reset(&b.shader,log2);b.shader.bindCommonParameters();
 if(errors || originalErrors || n!=eventCount || !equal(log1,log2,n*sizeof(Event)) || !equal(&a,&b,sizeof(a)))return 1;
 if(!equal(a.before,initial.before,sizeof(a.before)) || !equal(a.after,initial.after,sizeof(a.after)) ||
    !equal(a.shader.unknown00,initial.shader.unknown00,sizeof(a.shader.unknown00)))return 2;
 if(!mutate) {
  if(a.shader.vertexConstants!=initial.shader.vertexConstants || a.shader.pixelConstants!=initial.shader.pixelConstants)return 3;
  for(unsigned j=0;j<16;++j) {
   unsigned table=(j==0 || j==11 || j>=14)?0:1;
   // Both reposition requests find the first duplicate at index zero.
   unsigned index=j==1?0:j;
   ParameterHandle expected=0;
   if(!(nulls&(1u<<table)) && st==0 && index<count && !(mask&(1u<<index))) expected=&handles[table][index];
   // If index zero is missing, the duplicate at index one can still match.
   if((j==0 || j==1) && !(nulls&(1u<<table)) && st==0 && (mask&1) && count>1 && !(mask&2))expected=&handles[table][1];
   if(*(ParameterHandle*)((char*)&a.shader+offsets[j])!=expected)return 4;
  }
 }
 return 0;
}
extern "C" int test_main() {
 static_assert(sizeof(Shader)==0x58,"shader prefix layout");
 static_assert(offsetof(Shader,vertexConstants)==0x10,"table offset");
 static_assert(offsetof(Shader,morphAmounts)==0x54,"last handle offset");
 tables[0].vtable=&vtable;tables[0].id=0;tables[1].vtable=&vtable;tables[1].id=1;
 // These paths never dereference the original requested string addresses.
 for(unsigned n=0;n<4;++n) {
  if(run(n,0,0,0,0) || run(n,1,16,0,0) || run(n,-1,16,0,0) || run(n,0,16,0xffff,0))return 10;
 }
 if((uintptr_t)&oracle_names!=0x9fff74u) {
  const char msg[]="LIMIT: 16 null/empty/failure/null-handle differential cases passed; map .oracle_names at 0x9fff74 for the full 430-case suite.\n";
  test_write(msg,sizeof(msg)-1);return 0;
 }
 for(unsigned n=0;n<4;++n)for(unsigned c=0;c<=16;++c) {
  const uint32_t masks[]={0,1,3,0xaaaa,0x5555,0xffff};
  for(unsigned m=0;m<6;++m)if(run(n,0,c,masks[m],0))return 20;
 }
 for(unsigned m=1;m<=2;++m) {
  if(run(0,0,16,0,m) || run(0,-1,16,0,m) || run(0,0,16,0x5555,m))return 30;
 }
 const char msg[]="shader-common-parameters: 430 differential cases passed\n";
 test_write(msg,sizeof(msg)-1);return 0;
}
