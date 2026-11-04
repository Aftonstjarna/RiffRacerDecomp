#include "impl.hpp"
inline void* operator new(size_t,void* p) noexcept {return p;}
using riff::ShadowDrawShader;
extern "C" ShadowDrawShader* __attribute__((thiscall)) original_shader_shadowdraw_ctor(ShadowDrawShader*,uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
extern "C" void* memset(void*d,int c,unsigned n){for(unsigned i=0;i<n;++i)((uint8_t*)d)[i]=(uint8_t)c;return d;}
extern "C" void* memcpy(void*d,const void*s,unsigned n){for(unsigned i=0;i<n;++i)((uint8_t*)d)[i]=((const uint8_t*)s)[i];return d;}
static bool equal(const void*a,const void*b,unsigned n){for(unsigned i=0;i<n;++i)if(((const uint8_t*)a)[i]!=((const uint8_t*)b)[i])return false;return true;}
// Qualified test data only, no instructions. Includes exact-name fixtures,
// security cookie at baabc0 and manager pointer at bfcd04.
unsigned char oracle_data[0x200000] __attribute__((section(".oracle_data"),used,aligned(4)))={0};
static uint32_t fsStorage[64];
struct Name {uint32_t address;const char* text;};
static const Name names[]={
{0x9fe740,"matWorldViewProj"},{0xa013b0,"texelOffset"},
{0x9fffac,"g_repositionParams"},{0x9fff80,"gFogParams"},
{0x9fff74,"gFogColour"},{0x9fff98,"gFogHeightParams"},
{0x9fff8c,"alphaValue"},{0xa00008,"g_specularScale"},
{0x9ffff8,"g_specularPower"},{0xa00028,"g_ambientColor"},
{0xa00018,"g_diffuseColor"},{0x9fffd0,"g_specularColor"},
{0x9fffc0,"shadowMapPos"},{0x9fffec,"maskColor"},
{0x9fffe0,"shadowColor"},{0xa00048,"skinMatrixArray"},
{0xa00038,"g_morphAmounts"}};
struct Table {void** vt;uint32_t id;};
static void* vt[9];static Table tables[2];static uint32_t managerData[512],savedManager[512];
struct Desc {uint32_t creator,version,count;};
struct Param {const char* name;uint32_t remainder[11];};
struct Event {uint32_t kind,id,index,count;uint8_t object[0x70];};
static Event logs[2][2048];
static unsigned which,eventCount,bad,describeCount,constantCount,missing,mutate;
static int32_t tableStatus;
static ShadowDrawShader* active;
static void event(unsigned k,Table*t,unsigned i,unsigned c){
 if(eventCount>=2048){++bad;return;}
 Event&e=logs[which][eventCount++];e.kind=k;e.id=t->id;e.index=i;e.count=c;
 memcpy(e.object,active,sizeof(*active));
}
static int32_t RIFF_STDCALL describe(Table*t,Desc*d){
 event(1,t,0,0);d->creator=0;d->version=0;d->count=constantCount;
 ++describeCount;
 // Mutation during the first lookup exercises reloads for both texel calls
 // and the subsequent common helper. It also leaves changes in untouched-
 // by-constructor fields observable at the precise callback boundaries.
 if(mutate && describeCount==1){
  active->vertexConstants=(uint32_t)&tables[1];
  active->pixelConstants=mutate==1?(uint32_t)&tables[0]:0;
  active->unknown64=0x87654321;active->reserved0c=0x10203040;
 }
 return tableStatus;
}
static uint32_t RIFF_STDCALL constant(Table*t,uint32_t parent,unsigned i){
 event(2,t,i,0);if(parent || i>=17){++bad;return 0;}
 return (missing && i%missing==0)?0:0x1000+t->id*0x100+i;
}
static int32_t RIFF_STDCALL parameter(Table*t,uint32_t h,Param*d,uint32_t*c){
 unsigned i=h-0x1000-t->id*0x100;event(3,t,i,*c);
 if(i>=17 || *c!=1){++bad;return -1;}
 d->name=names[i].text;*c=7;return -1; // Original ignores description HRESULT.
}
static void reset(ShadowDrawShader*p,unsigned w){active=p;which=w;eventCount=bad=describeCount=0;}
struct Guarded {uint32_t before[4];alignas(ShadowDrawShader) uint8_t object[0x70];uint32_t after[4];};
static uint32_t word(const void*p,unsigned o){return *(const uint32_t*)((const uint8_t*)p+o);}
static uint32_t expectedHandle(unsigned name,unsigned table,unsigned nulls){
 return (nulls&(1u<<table)) || tableStatus || name>=constantCount || (missing && name%missing==0)
        ?0:0x1000+table*0x100+name;
}
static int run(uint32_t index,unsigned nulls,unsigned serial){
 Guarded a,b;for(unsigned i=0;i<sizeof(a);++i)((uint8_t*)&a)[i]=(uint8_t)(i*37+serial);b=a;
 const unsigned slot=(index*16u)/4u;
 for(unsigned i=0;i<512;++i)managerData[i]=0xdead0000+i;
 managerData[slot+2]=0x11110000+serial;managerData[slot+4]=0x22220000+serial;
 managerData[slot+3]=(nulls&1)?0:(uint32_t)&tables[0];
 managerData[slot+5]=(nulls&2)?0:(uint32_t)&tables[1];
 memcpy(savedManager,managerData,sizeof(managerData));
 *(uint32_t*)(oracle_data+0xbfcd04-0x9fe000)=(uint32_t)managerData;
 reset((ShadowDrawShader*)a.object,0);
 ShadowDrawShader*x=new(a.object) ShadowDrawShader(index);
 unsigned count=eventCount;
 if(x!=(ShadowDrawShader*)a.object || bad || test_get_fs_head()!=fsStorage[0])return 1;
 reset((ShadowDrawShader*)b.object,1);
 unsigned head=test_get_fs_head();
 ShadowDrawShader*y=original_shader_shadowdraw_ctor((ShadowDrawShader*)b.object,index);
 // No fallback when FS setup or fixed data mapping is unavailable.
 if(test_get_fs_head()!=head || head!=0xfedcba98)return 2;
 if(y!=(ShadowDrawShader*)b.object || bad || count!=eventCount ||
    !equal(&a,&b,sizeof(a)) || !equal(logs[0],logs[1],count*sizeof(Event)))return 3;
 if(!equal(managerData,savedManager,sizeof(managerData)))return 4;
 for(unsigned i=0;i<4;++i)if(a.before[i]!=b.before[i] || a.after[i]!=b.after[i])return 5;
 // Independently check canaries against their initial values (not just parity).
 for(unsigned i=0;i<16;++i){
  if(((uint8_t*)a.before)[i]!=(uint8_t)(i*37+serial))return 6;
  if(((uint8_t*)a.after)[i]!=(uint8_t)((16+0x70+i)*37+serial))return 7;
 }
 if(x->vtable!=0xa013d8 || x->shaderIndex!=index || x->unknown68 ||
    x->vertexShader!=managerData[slot+2] || x->pixelShader!=managerData[slot+4])return 8;
 if(!mutate){
  if(x->reserved0c || x->unknown64 || x->vertexConstants!=managerData[slot+3] ||
     x->pixelConstants!=managerData[slot+5])return 9;
  if(x->worldViewProjection!=expectedHandle(0,0,nulls) ||
     x->vertexTexelOffset!=expectedHandle(1,0,nulls) ||
     x->pixelTexelOffset!=expectedHandle(1,1,nulls))return 10;
  // common call order differs from destination order at +2c and +44.
  const unsigned nameIndex[16]={2,2,3,4,5,12,6,7,8,9,10,11,13,14,15,16};
  for(unsigned i=0;i<16;++i){unsigned table=(i==0 || i==5 || i==14 || i==15)?0:1;
   if(word(a.object,0x18+4*i)!=expectedHandle(nameIndex[i],table,nulls))return 11;
  }
 }
 return 0;
}
extern "C" int test_main(){
 if((uintptr_t)oracle_data!=0x9fe000 || sizeof(oracle_data)!=0x200000)return 20;
 fsStorage[0]=0xfedcba98;
 if(test_install_fs(fsStorage)!=0 || test_get_fs_head()!=0xfedcba98)return 21;
 for(unsigned i=0;i<17;++i){unsigned j=0;do{oracle_data[names[i].address-0x9fe000+j]=names[i].text[j];}while(names[i].text[j++]);}
 *(uint32_t*)(oracle_data+0xbaabc0-0x9fe000)=0x12345678;
 vt[5]=(void*)describe;vt[6]=(void*)parameter;vt[8]=(void*)constant;
 for(unsigned i=0;i<2;++i){tables[i].vt=vt;tables[i].id=i;}
 const uint32_t indices[]={0,1,119,120,121,122,123,124,125,0x10000000u,0x80000077u,0xf000007du};
 unsigned serial=0;
 for(unsigned k=0;k<12;++k)for(unsigned n=0;n<4;++n)for(unsigned st=0;st<3;++st)
 for(unsigned ct=0;ct<4;++ct)for(missing=0;missing<3;++missing)for(mutate=0;mutate<3;++mutate){
  tableStatus=st==0?0:st==1?1:-1;constantCount=ct==0?0:ct==1?1:ct==2?2:17;
  int r=run(indices[k],n,serial++);if(r)return r;
 }
 const char msg[]="PASS: 5184 original/constructor comparisons, FS restored\n";
 test_write(msg,sizeof(msg)-1);return 0;
}
