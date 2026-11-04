#include "impl.hpp"
inline void* operator new(size_t,void* p) noexcept {return p;}
using namespace riff;
extern "C" NormalMappedShader* __attribute__((thiscall)) original_shader_normalmapped_ctor(NormalMappedShader*,uint32_t,const char*,uint32_t);
extern "C" NormalMappedShader* __attribute__((thiscall)) original_shader_base_ctor(NormalMappedShader*);
extern "C" void __attribute__((thiscall)) original_shader_common_parameters(NormalMappedShader*);
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
{0xa017b0,"lightDir"},
{0xa017bc,"lightDir2"},
{0xa017ec,"lightDir3"},
{0x9fe704,"lightAmbient"},
{0x9fe6e8,"lightDiffuse"},
{0x9fe714,"lightSpecular"},
{0x9fe7a0,"lightPoints"},
{0x9fe788,"g_lightFalloffDistance"},
{0x9fe7b8,"g_attenuationFactor"},
{0xa017f8,"g_dirtScale"},
{0xa017c8,"g_dirtColor"},
{0xa017d4,"g_screenSpaceUVAdjust"},
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
static Table tables[2];static void* vt[9];static uint32_t managerData[512];
struct Desc {uint32_t creator,version,count;};
struct Param {const char* name;uint32_t remainder[11];};
struct Event {uint32_t kind,id,index,count;uint8_t object[0x114];};
static Event logs[2][4096];static unsigned which,eventCount,bad,describeCount;
static NormalMappedShader* active;static unsigned constantCount,mutate,missing;static int32_t tableStatus;
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
 event(2,t,i,0);if(parent||i>=31){++bad;return 0;}
 return (missing && (i%missing==0))?0:0x1000+t->id*0x100+i;
}
static int32_t RC_STDCALL parameter(Table*t,uint32_t h,Param*d,uint32_t*c){
 unsigned i=h-0x1000-t->id*0x100;event(3,t,i,*c);
 if(i>=31 || *c!=1){++bad;return -1;}
 d->name=names[i].text;*c=7;return -1; // Lookup ignores this return status.
}
static void reset(NormalMappedShader*p,unsigned w){active=p;which=w;eventCount=bad=describeCount=0;}
struct Guarded {uint32_t before[4]; alignas(NormalMappedShader) uint8_t object[0x114];uint32_t after[4];};
static const unsigned handleOffsets[]={0x5c,0x60,0x64,0x68,0x6c,0x70,0x74,0x78,0x7c,0x80,0xf4,0xf8,0xfc,0x100,0x104,0x108};
static uint32_t word(const void*p,unsigned o){return *(const uint32_t*)((const uint8_t*)p+o);}
static void put(void*p,unsigned o,uint32_t w){*(uint32_t*)((uint8_t*)p+o)=w;}
static int run(uint32_t index,unsigned nulls,const char* name,uint32_t arg,unsigned serial,bool mapped){
 Guarded initial,a,b,c;for(unsigned i=0;i<sizeof(initial);++i)((uint8_t*)&initial)[i]=(uint8_t)(i*37+serial);
 a=initial;b=initial;c=initial;
 unsigned slot=(index*16u)/4u; // wrap is intentional; index aliases exercise x86 wrap.
 for(unsigned i=0;i<512;++i)managerData[i]=0xdead0000+i;
 managerData[slot+2]=0x11110000+serial;managerData[slot+4]=0x22220000+serial;
 managerData[slot+3]=(nulls&1)?0:(uint32_t)&tables[0];
 managerData[slot+5]=(nulls&2)?0:(uint32_t)&tables[1];
 oracle_manager=managerData;
 NormalMappedServices s={original_shader_base_ctor,original_shader_parameter_lookup,original_shader_common_parameters,managerData};
 NormalMappedShader* x=(NormalMappedShader*)a.object;reset(x,0);
 if(x->construct(index,name,arg,s)!=x || bad)return 1;
 unsigned count=eventCount;
 // Independently verify write footprint, borrowed pointer, matrix and handles.
 Guarded expected=initial;
 const unsigned always[]={0,4,8,12,16,20,0x58};
 for(unsigned i=0;i<sizeof(always)/sizeof(always[0]);++i)put(expected.object,always[i],word(a.object,always[i]));
 for(unsigned o=0x18;o<=0x54;o+=4)put(expected.object,o,word(a.object,o));
 for(unsigned i=0;i<16;++i)put(expected.object,handleOffsets[i],word(a.object,handleOffsets[i]));
 for(unsigned i=0;i<16;++i){uint32_t v=i%5==0?0x3f800000:0;put(expected.object,0x84+i*4,v);if(word(a.object,0x84+i*4)!=v)return 2;}
 expected.object[0x110]=index==0x53;expected.object[0x111]=index==0x5b;
 if(!equal(&expected,&a,sizeof(a)) || x->name!=name || x->argument!=arg ||
    x->vtable!=0xa01808 || x->isIndex53!=(index==0x53) || x->isIndex5b!=(index==0x5b) ||
    x->vertexShader!=managerData[slot+2] || x->pixelShader!=managerData[slot+4])return 3;
 if(!mutate)for(unsigned i=0;i<16;++i){
  bool null=(nulls&((i<7 || i==10)?1:2))!=0;
  uint32_t h=(!null && !tableStatus && i<constantCount && !(missing && i%missing==0))?0x1000+((i<7 || i==10)?0:0x100)+i:0;
  if(word(a.object,handleOffsets[i])!=h)return 4;
 }
 if(mapped){
  NormalMappedShader*y=(NormalMappedShader*)b.object;reset(y,1);uint32_t fs=oracle_tls[0];
  if(original_shader_normalmapped_ctor(y,index,name,arg)!=y || bad || eventCount!=count ||
    !equal(&a,&b,sizeof(a)) || !equal(logs[0],logs[1],count*sizeof(Event)) || oracle_tls[0]!=fs)return 5;
  reset((NormalMappedShader*)c.object,1);
  NormalMappedShader*z=new(c.object) NormalMappedShader(index,name,arg);
  if(z!=(NormalMappedShader*)c.object || bad || eventCount!=count || !equal(&a,&c,sizeof(a)) ||
     !equal(logs[0],logs[1],count*sizeof(Event)))return 6;
 }
 return 0;
}
extern "C" int test_main(){
 bool mapped=(uintptr_t)oracle_names==0x9fe000 && (uintptr_t)&oracle_cookie==0xbaabc0 &&
             (uintptr_t)&oracle_manager==0xbfcd04 && (uintptr_t)oracle_tls==0xbac000;
 if(mapped){for(unsigned i=0;i<31;++i){unsigned j=0;do{oracle_names[names[i].address-0x9fe000+j]=names[i].text[j];}while(names[i].text[j++]);}}
 else {
  // The minimal trusted linker has no fixed data or FS fixtures. Exercise
  // the adapter with real accepted base/common/lookup helpers and null tables;
  // do not pretend this executes the SEH-bearing target. Full target tests
  // are the separately executed mapped/TLS suite below (build.py and run_oracle.py).
  constantCount=31;tableStatus=0;missing=0;mutate=0;
  for(unsigned i=0;i<16;++i){int r=run(i%13,3,(i&1)?"normalmapped":0,i*0x11111111u,i,false);if(r)return r;}
  const char msg[]="PASS: null-table adapter checks; full oracle suite requires fixed data and FS\n";
  test_write(msg,sizeof(msg)-1);return 0;
 }
 vt[5]=(void*)describe;vt[6]=(void*)parameter;vt[8]=(void*)constant;
 for(unsigned i=0;i<2;++i){tables[i].vt=vt;tables[i].id=i;}
 unsigned serial=0;
 const uint32_t indices[]={0,1,0x51,0x52,0x53,0x54,0x5a,0x5b,0x5c,0x10000000u,0x80000053u,0xf000005bu};
 const uint32_t args[]={0,1,0x80000000u,0xffffffffu};
 const char label[]="normalmapped test";
 for(unsigned k=0;k<12;++k)for(unsigned n=0;n<4;++n)for(unsigned ai=0;ai<4;++ai)
 for(unsigned st=0;st<3;++st)for(unsigned ct=0;ct<4;++ct)for(missing=0;missing<3;++missing)for(mutate=0;mutate<3;++mutate){
  constantCount=ct==0?0:ct==1?7:ct==2?16:31;tableStatus=st==0?0:st==1?1:-1;
  int r=run(indices[k],n,(serial&1)?label:0,args[ai],serial,mapped);if(r)return r;++serial;
 }
 const char msg[]="PASS: 20736 original/adapter/constructor comparisons\n";
 test_write(msg,sizeof(msg)-1);
 return 0;
}
