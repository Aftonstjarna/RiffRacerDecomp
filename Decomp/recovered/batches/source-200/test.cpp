#include "impl.hpp"
inline void* operator new(size_t,void* p) noexcept {return p;}
using namespace riff;
extern "C" GlassShader* __attribute__((thiscall)) original_shader_glass_ctor(GlassShader*,uint32_t,const char*,uint32_t);
extern "C" GlassShader* __attribute__((thiscall)) original_shader_base_ctor(GlassShader*);
extern "C" void __attribute__((thiscall)) original_shader_common_parameters(GlassShader*);
extern "C" uint32_t __attribute__((stdcall)) original_shader_parameter_lookup(uint32_t,const char*);
extern "C" void test_write(const char*,unsigned);
extern "C" void* memset(void*d,int c,unsigned n){for(unsigned i=0;i<n;++i)((uint8_t*)d)[i]=(uint8_t)c;return d;}
extern "C" void* memcpy(void*d,const void*s,unsigned n){for(unsigned i=0;i<n;++i)((uint8_t*)d)[i]=((const uint8_t*)s)[i];return d;}
static bool equal(const void*a,const void*b,unsigned n){for(unsigned i=0;i<n;++i)if(((const uint8_t*)a)[i]!=((const uint8_t*)b)[i])return false;return true;}
// Test-only fixed-address data. Link .names at 9fe000, .cookie at baabc0,
// .manager at bfcd04, .tls at bac000; launcher installs FS based at .tls.
char oracle_names[0x4000] __attribute__((section(".names"),aligned(4096)))={0};
uint32_t oracle_cookie __attribute__((section(".cookie"),aligned(4)))=0x12345678;
const uint32_t* oracle_manager __attribute__((section(".manager"),aligned(4)))=0;
uint32_t oracle_tls[1024] __attribute__((section(".tls"),aligned(4096)))={0};
struct Name {unsigned address; const char* text;};
static const Name names[]={
{0x9fe740,"matWorldViewProj"},
{0x9fe764,"matWorld"},
{0x9fe754,"matWorldInverse"},
{0x9fe7ac,"cameraPos"},
{0xa01690,"matInvView"},
{0xa017b0,"lightDir"},
{0x9fe704,"lightAmbient"},
{0x9fe6e8,"lightDiffuse"},
{0x9fe714,"lightSpecular"},
{0xa01924,"s_reflectionStrength"},
{0xa01900,"s_glassColor"},
{0xa01910,"g_reflectionColor"},
{0xa018e0,"g_illuminateColor"},
{0xa018f4,"s_cubeColor"},
{0x9fffac,"g_repositionParams"},
{0x9fff80,"gFogParams"},
{0x9fff74,"gFogColour"},
{0x9fff98,"gFogHeightParams"},
{0x9fff8c,"alphaValue"},
{0xa00008,"g_specularScale"},
{0x9ffff8,"g_specularPower"},
{0xa00028,"g_ambientColor"},
{0xa00018,"g_diffuseColor"},
{0x9fffd0,"g_specularColor"},
{0x9fffc0,"shadowMapPos"},
{0x9fffec,"maskColor"},
{0x9fffe0,"shadowColor"},
{0xa00048,"skinMatrixArray"},
{0xa00038,"g_morphAmounts"},
};
// These callbacks implement a synthetic constant-table boundary, while all
// lookup/enumeration behavior is performed by the actual accepted oracle.
struct Table {void** vt;unsigned id;};
static Table tables[2];static void* vt[9];static uint32_t managerData[64];
struct Desc {uint32_t creator,version,count;};
struct Param {const char* name;uint32_t remainder[11];};
struct Event {uint32_t kind,id,index,count;uint8_t object[0xfc];};
static Event logs[2][4096];static unsigned which,eventCount,bad,describeCount;
static GlassShader* active;static unsigned constantCount,mutate,missing;static int32_t tableStatus;
static void event(unsigned k,Table*t,unsigned i,unsigned c){
 if(eventCount>=4096){++bad;return;} Event&e=logs[which][eventCount++];
 e.kind=k;e.id=t->id;e.index=i;e.count=c;memcpy(e.object,active,sizeof(*active));
}
static int32_t RC_STDCALL describe(Table*t,Desc*d){
 event(1,t,0,0); d->creator=0;d->version=0;d->count=constantCount;
 ++describeCount;
 if(mutate && describeCount==3){active->vertexConstants=(uint32_t)&tables[1];active->pixelConstants=mutate==1?(uint32_t)&tables[0]:0;}
 return tableStatus;
}
static uint32_t RC_STDCALL constant(Table*t,uint32_t parent,unsigned i){
 event(2,t,i,0);if(parent||i>=29){++bad;return 0;}
 return (missing && (i%missing==0))?0:0x1000+t->id*0x100+i;
}
static int32_t RC_STDCALL parameter(Table*t,uint32_t h,Param*d,uint32_t*c){
 unsigned i=h-0x1000-t->id*0x100;event(3,t,i,*c);
 if(i>=29 || *c!=1){++bad;return -1;}
 d->name=names[i].text;*c=7;return -1; // Lookup ignores this return status.
}
static void reset(GlassShader*p,unsigned w){active=p;which=w;eventCount=bad=describeCount=0;}
struct Guarded {uint32_t before[4]; alignas(GlassShader) uint8_t object[0xfc];uint32_t after[4];};
static const unsigned handleOffsets[]={0x60,0x64,0x68,0x6c,0xc4,0x70,0x74,0x78,0x7c,0xc8,0xcc,0xd4,0xd8,0xd0};
static uint32_t word(const void*p,unsigned o){return *(const uint32_t*)((const uint8_t*)p+o);}
static void put(void*p,unsigned o,uint32_t w){*(uint32_t*)((uint8_t*)p+o)=w;}
static int run(uint32_t index,unsigned nulls,const char* name,uint32_t arg,unsigned serial,bool mapped){
 Guarded initial,a,b,c;for(unsigned i=0;i<sizeof(initial);++i)((uint8_t*)&initial)[i]=(uint8_t)(i*37+serial);
 a=initial;b=initial;c=initial;
 unsigned slot=(index*16u)/4u; // wrap is intentional; index aliases exercise x86 wrap.
 for(unsigned i=0;i<64;++i)managerData[i]=0xdead0000+i;
 managerData[slot+2]=0x11110000+serial;managerData[slot+4]=0x22220000+serial;
 managerData[slot+3]=(nulls&1)?0:(uint32_t)&tables[0];
 managerData[slot+5]=(nulls&2)?0:(uint32_t)&tables[1];
 oracle_manager=managerData;
 GlassServices s={original_shader_base_ctor,original_shader_parameter_lookup,original_shader_common_parameters,managerData};
 GlassShader* x=(GlassShader*)a.object;reset(x,0);
 if(x->construct(index,name,arg,s)!=x || bad)return 1;
 unsigned count=eventCount;
 // Independently verify write footprint, borrowed pointer, matrix and handles.
 Guarded expected=initial;
 const unsigned always[]={0,4,8,12,16,20,0x58,0x5c,0xec,0xf0,0xf4};
 for(unsigned i=0;i<sizeof(always)/sizeof(always[0]);++i)put(expected.object,always[i],word(a.object,always[i]));
 for(unsigned o=0x18;o<=0x54;o+=4)put(expected.object,o,word(a.object,o));
 for(unsigned i=0;i<14;++i)put(expected.object,handleOffsets[i],word(a.object,handleOffsets[i]));
 for(unsigned i=0;i<16;++i){uint32_t v=i%5==0?0x3f800000:0;put(expected.object,0x84+i*4,v);if(word(a.object,0x84+i*4)!=v)return 2;}
 expected.object[0xf8]=0;
 if(!equal(&expected,&a,sizeof(a)) || x->name!=name || x->argument!=arg || x->shaderIndex!=index ||
    x->vtable!=0xa01940 || x->reserved5c || x->unknownF0 || x->memberF4 || x->flagF8 ||
    x->vertexShader!=managerData[slot+2] || x->pixelShader!=managerData[slot+4])return 3;
 if(!mutate)for(unsigned i=0;i<14;++i){
  bool null=(nulls&(i<6?1:2))!=0;
  uint32_t h=(!null && !tableStatus && i<constantCount && !(missing && i%missing==0))?0x1000+(i<6?0:0x100)+i:0;
  if(word(a.object,handleOffsets[i])!=h)return 4;
 }
 if(mapped){
  GlassShader*y=(GlassShader*)b.object;reset(y,1);uint32_t fs=oracle_tls[0];
  if(original_shader_glass_ctor(y,index,name,arg)!=y || bad || eventCount!=count ||
    !equal(&a,&b,sizeof(a)) || !equal(logs[0],logs[1],count*sizeof(Event)) || oracle_tls[0]!=fs)return 5;
  reset((GlassShader*)c.object,1);
  GlassShader*z=new(c.object) GlassShader(index,name,arg);
  if(z!=(GlassShader*)c.object || bad || eventCount!=count || !equal(&a,&c,sizeof(a)) ||
     !equal(logs[0],logs[1],count*sizeof(Event)))return 6;
 }
 return 0;
}
extern "C" int test_main(){
 bool mapped=(uintptr_t)oracle_names==0x9fe000 && (uintptr_t)&oracle_cookie==0xbaabc0 &&
             (uintptr_t)&oracle_manager==0xbfcd04 && (uintptr_t)oracle_tls==0xbac000;
 if(mapped){for(unsigned i=0;i<29;++i){unsigned j=0;do{oracle_names[names[i].address-0x9fe000+j]=names[i].text[j];}while(names[i].text[j++]);}}
 else {
  // The minimal trusted linker has no fixed data or FS fixtures. Exercise
  // the adapter with real accepted base/common/lookup helpers and null tables;
  // do not pretend this executes the SEH-bearing target. Full target tests
  // are the separately executed mapped/TLS suite below (build.py and run_oracle.py).
  constantCount=29;tableStatus=0;missing=0;mutate=0;
  for(unsigned i=0;i<16;++i){int r=run(i%13,3,(i&1)?"glass":0,i*0x11111111u,i,false);if(r)return r;}
  const char msg[]="PASS: null-table adapter checks; full oracle suite requires fixed data and FS\n";
  test_write(msg,sizeof(msg)-1);return 0;
 }
 vt[5]=(void*)describe;vt[6]=(void*)parameter;vt[8]=(void*)constant;
 for(unsigned i=0;i<2;++i){tables[i].vt=vt;tables[i].id=i;}
 unsigned serial=0;
 const uint32_t indices[]={0,1,12,0x10000000u,0x80000001u,0xf000000cu};
 const uint32_t args[]={0,1,0x80000000u,0xffffffffu};
 const char label[]="glass test";
 for(unsigned k=0;k<6;++k)for(unsigned n=0;n<4;++n)for(unsigned ai=0;ai<4;++ai)
 for(unsigned st=0;st<3;++st)for(unsigned ct=0;ct<4;++ct)for(missing=0;missing<3;++missing)for(mutate=0;mutate<3;++mutate){
  constantCount=ct==0?0:ct==1?7:ct==2?14:29;tableStatus=st==0?0:st==1?1:-1;
  int r=run(indices[k],n,(serial&1)?label:0,args[ai],serial,mapped);if(r)return r;++serial;
 }
 const char msg[]="PASS: 10368 original/adapter/constructor comparisons\n";
 test_write(msg,sizeof(msg)-1);
 return 0;
}
