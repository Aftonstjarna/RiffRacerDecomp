#include "impl.hpp"
inline void* operator new(size_t,void* p) noexcept {return p;}
extern "C" {
CarGlass* RIFF_THIS original_shader_carglass_ctor(CarGlass*,uint32_t,uint32_t);
void RIFF_THIS original_shader_base_ctor(CarGlass*);
void RIFF_THIS original_shader_common_parameters(CarGlass*);
int test_install_fs(void*);
unsigned test_get_fs_head();
void test_write(const char*,unsigned);
}
// Exact qualified data region, including names, cookie and manager slot.
uint8_t fixture[0x201000] __attribute__((section(".fixture"),used,aligned(4)))={0};
ShaderManager* shader_manager;
static unsigned helperFsError;
void RIFF_THIS CarGlass::initializeBase(){unsigned head=test_get_fs_head();original_shader_base_ctor(this);if(test_get_fs_head()!=head)helperFsError=1;}
void RIFF_THIS CarGlass::initializeCommonParameters(){unsigned head=test_get_fs_head();original_shader_common_parameters(this);if(test_get_fs_head()!=head)helperFsError=1;}
extern "C" void* memset(void*d,int c,unsigned n){for(unsigned i=0;i<n;++i)((uint8_t*)d)[i]=(uint8_t)c;return d;}
extern "C" void* memcpy(void*d,const void*s,unsigned n){for(unsigned i=0;i<n;++i)((uint8_t*)d)[i]=((const uint8_t*)s)[i];return d;}
static bool equal(const void*a,const void*b,unsigned n){for(unsigned i=0;i<n;++i)if(((const uint8_t*)a)[i]!=((const uint8_t*)b)[i])return false;return true;}
struct Name {uint32_t address;const char* text;};
static const Name names[]={
{0x9fe740,"matWorldViewProj"},{0xa01690,"matInvView"},{0xa0169c,"vCameraPos"},
{0xa016bc,"diffuse"},{0xa016c4,"reflectiveness"},
{0x9fffac,"g_repositionParams"},{0x9fff80,"gFogParams"},{0x9fff74,"gFogColour"},
{0x9fff98,"gFogHeightParams"},{0x9fff8c,"alphaValue"},{0xa00008,"g_specularScale"},
{0x9ffff8,"g_specularPower"},{0xa00028,"g_ambientColor"},{0xa00018,"g_diffuseColor"},
{0x9fffd0,"g_specularColor"},{0x9fffc0,"shadowMapPos"},{0x9fffec,"maskColor"},
{0x9fffe0,"shadowColor"},{0xa00048,"skinMatrixArray"},{0xa00038,"g_morphAmounts"}};
struct Resource {ResourceVtable* vt;uint32_t id;};
static Resource resources[2];
static CarGlass* active;
static unsigned mode,mutation,missing,error,count,namedCount,serial;
struct Event {uint32_t kind,id,a,b;uint8_t object[sizeof(CarGlass)];};
static Event events[2048],saved[2048];
static void record(unsigned kind,Resource*r,unsigned a,unsigned b){
 if(count>=2048){error=1;return;}
 Event& e=events[count++];e.kind=kind;e.id=r->id;e.a=a;e.b=b;memcpy(e.object,active,sizeof(*active));
}
static bool textEqual(const char*a,const char*b){while(*a && *a==*b){++a;++b;}return *a==*b;}
static unsigned nameIndex(const char*s){for(unsigned i=0;i<20;++i)if(textEqual(s,names[i].text))return i;error=2;return 99;}
static uint32_t handle(Resource*r,unsigned i){return mode==0?0:((serial+1)*0x1020304u ^ (r->id*0x76543210u) ^ (i+1));}
static uint32_t RIFF_STDCALL named(ShaderResource*p,uint32_t parent,const char*s){
 Resource*r=(Resource*)p;unsigned i=nameIndex(s);record(9,r,parent,i);
 if(parent || i!=namedCount || namedCount>=5)error=3;
 ++namedCount;
 // Exercise fresh field reads on subsequent calls, including the vertex/pixel boundary.
 if(mutation && namedCount==1)active->vertexParameters=(ShaderResource*)&resources[1];
 if(mutation && namedCount==3)active->pixelParameters=(ShaderResource*)&resources[0];
 return handle(r,i);
}
static uint32_t RIFF_STDCALL describe(ShaderResource*p,uint32_t*d){
 record(5,(Resource*)p,0,0);d[0]=0x1234;d[1]=0;d[2]=mode==3?20:mode==4?3:0;
 return mode==2?0x80004005u:0;
}
static uint32_t RIFF_STDCALL byIndex(ShaderResource*p,uint32_t parent,uint32_t i){
 Resource*r=(Resource*)p;record(8,r,parent,i);if(parent || i>=20)error=4;
 return (mode==4 || (missing && i%3==0))?0:0x1000+r->id*0x100+i;
}
struct Parameter {const char* name;uint32_t rest[11];};
static uint32_t RIFF_STDCALL parameter(ShaderResource*p,uint32_t h,Parameter*d,uint32_t*n){
 Resource*r=(Resource*)p;unsigned i=h-0x1000-r->id*0x100;record(6,r,i,*n);
 if(i>=20 || *n!=1){error=5;return -1u;}
 memset(d,0,sizeof(*d));d->name=names[i].text;*n=7;
 return -1u; // accepted helper ignores descriptor status
}
static void reset(CarGlass*p){active=p;count=error=namedCount=0;memset(events,0,sizeof(events));}
static uint32_t word(const void*p,unsigned o){return *(const uint32_t*)((const uint8_t*)p+o);}
extern "C" int test_main(){
 if((uintptr_t)fixture!=0x9fe000 || sizeof(fixture)!=0x201000)return 1;
 uint32_t fs[16];memset(fs,0x6b,sizeof(fs));fs[0]=0xffffffffu;
 if(test_install_fs(fs)!=0 || test_get_fs_head()!=fs[0])return 2;
 for(unsigned i=0;i<20;++i){unsigned j=0;do{fixture[names[i].address-0x9fe000+j]=(uint8_t)names[i].text[j];}while(names[i].text[j++]);}
 *(uint32_t*)(fixture+0xbaabc0-0x9fe000)=0x12345678;
 ResourceVtable vt={};vt.unused[5]=(uint32_t)(uintptr_t)&describe;vt.unused[6]=(uint32_t)(uintptr_t)&parameter;vt.unused[8]=(uint32_t)(uintptr_t)&byIndex;vt.namedParameter=&named;
 resources[0].vt=&vt;resources[0].id=1;resources[1].vt=&vt;resources[1].id=2;
 ShaderManager manager,before;memset(&manager,0x71,sizeof(manager));shader_manager=&manager;
 *(ShaderManager**)(fixture+0xbfcd04-0x9fe000)=&manager;
 static uint8_t fixtureBefore[sizeof(fixture)];memcpy(fixtureBefore,fixture,sizeof(fixture));
 const uint32_t flags[]={0,1,2,0x7f,0x80,0xff,0x100,0xffffff01u,0xffffffffu};
 serial=0;
 for(mode=0;mode<5;++mode)for(mutation=0;mutation<2;++mutation)for(missing=0;missing<2;++missing)
 for(unsigned alias=0;alias<2;++alias)for(unsigned fill=0;fill<2;++fill)for(unsigned f=0;f<9;++f){
  manager.vertexProgram=0x87654321u+serial;manager.pixelProgram=~manager.vertexProgram;
  manager.vertexParameters=(ShaderResource*)&resources[0];manager.pixelParameters=(ShaderResource*)&resources[alias?0:1];before=manager;
  struct Guarded {uint32_t pre[4];CarGlass object;uint32_t post[4];};
  // Raw storage avoids invoking the constructor during fixture setup.
  alignas(Guarded) uint8_t aa[sizeof(Guarded)],bb[sizeof(Guarded)],cc[sizeof(Guarded)];
  memset(aa,fill?0xff:0xa5,sizeof(aa));memcpy(bb,aa,sizeof(aa));memcpy(cc,aa,sizeof(aa));
  Guarded*a=(Guarded*)aa;Guarded*b=(Guarded*)bb;Guarded*c=(Guarded*)cc;
  uint32_t first=flags[f],second=flags[(f*2+3)%9];
  reset(&a->object);
  if(original_shader_carglass_ctor(active,first,second)!=active)return 3;
  if(test_get_fs_head()!=fs[0] || fs[1]!=0x6b6b6b6b)return 4;
  if(error || helperFsError || namedCount!=5)return 5;
  unsigned originalCount=count;memcpy(saved,events,count*sizeof(Event));
  reset(&b->object);if(active->construct((uint8_t)first,(uint8_t)second)!=active)return 6;
  if(test_get_fs_head()!=fs[0] || error || helperFsError || count!=originalCount || !equal(saved,events,count*sizeof(Event)) || !equal(aa,bb,sizeof(aa)))return 7;
  reset(&c->object);if(new(&c->object)CarGlass((uint8_t)first,(uint8_t)second)!=&c->object)return 8;
  if(test_get_fs_head()!=fs[0] || error || helperFsError || count!=originalCount || !equal(saved,events,count*sizeof(Event)) || !equal(aa,cc,sizeof(aa)))return 9;
  // Independent footprint checks: untouched flags padding, guards, all fields.
  uint32_t initial=fill?0xffffffffu:0xa5a5a5a5u;
  for(unsigned i=0;i<4;++i)if(a->pre[i]!=initial || a->post[i]!=initial)return 10;
  if(a->object.padding5a[0]!=(uint8_t)initial || a->object.padding5a[1]!=(uint8_t)initial)return 11;
  if(a->object.flag58!=(uint8_t)first || a->object.flag59!=(uint8_t)second || a->object.vtable!=0xa016d8 || a->object.member5c || a->object.unknownB4 || a->object.unknown0c)return 12;
  if(a->object.vertexProgram!=manager.vertexProgram || a->object.pixelProgram!=manager.pixelProgram)return 13;
  for(unsigned i=0;i<16;++i)if(word(&a->object,0x74+i*4)!=(i%5==0?0x3f800000u:0))return 14;
  for(unsigned i=0;i<5;++i){unsigned resource=i<3?(mutation && i>0?1:0):(mutation?0:(alias?0:1));if(word(&a->object,0x60+i*4)!=handle(&resources[resource],i))return 15;}
  if(!equal(&before,&manager,sizeof(manager)) || !equal(fixture,fixtureBefore,sizeof(fixture)) || resources[0].vt!=&vt || resources[1].vt!=&vt || resources[0].id!=1 || resources[1].id!=2)return 16;
  if(mode<3 || mode==4)for(unsigned i=0;i<16;++i)if(a->object.commonParameters[i])return 17;
  ++serial;
 }
 const char msg[]="PASS: 720 direct original/member/constructor cases; FS restored\n";test_write(msg,sizeof(msg)-1);return 0;
}
