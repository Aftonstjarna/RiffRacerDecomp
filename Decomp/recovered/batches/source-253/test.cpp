#include "impl.hpp"
#include <stddef.h>
using namespace riff;
extern "C" SeaShader* SEA_THIS original_shader_sea_ctor(SeaShader*);
extern "C" void SEA_THIS original_shader_base_ctor(SeaShader*);
extern "C" void SEA_THIS original_shader_common_parameters(SeaShader*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
unsigned char rdata[0xe0000] __attribute__((section(".oracle_rdata"),used,aligned(4)));
uint32_t cookie __attribute__((section(".oracle_cookie"),used,aligned(4)));
ShaderManager* managerFixture __attribute__((section(".oracle_manager"),used,aligned(4)));
uint32_t seh[8] __attribute__((section(".oracle_seh"),used,aligned(4)));
static unsigned dependencyFsError;
namespace riff {
ShaderManager* seaShaderManager;
void SEA_THIS SeaShader::initializeBase(){unsigned head=test_get_fs_head();original_shader_base_ctor(this);if(test_get_fs_head()!=head)dependencyFsError=1;}
void SEA_THIS SeaShader::bindCommonParameters(){unsigned head=test_get_fs_head();original_shader_common_parameters(this);if(test_get_fs_head()!=head)dependencyFsError=1;}
}
extern "C" void* memcpy(void* d,const void* s,unsigned n){unsigned char* a=(unsigned char*)d;const unsigned char* b=(const unsigned char*)s;for(unsigned i=0;i<n;++i)a[i]=b[i];return d;}
extern "C" void* memset(void* d,int v,unsigned n){unsigned char* a=(unsigned char*)d;for(unsigned i=0;i<n;++i)a[i]=(unsigned char)v;return d;}
static bool equal(const void* a,const void* b,unsigned n){const unsigned char* x=(const unsigned char*)a;const unsigned char* y=(const unsigned char*)b;for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;return true;}
static uint32_t hash(const char* s){uint32_t h=5381;while(*s)h=h*33+(unsigned char)*s++;return h;}
static void putName(unsigned a,const char* s){char* d=(char*)(rdata+a-0x92d000);do{*d++=*s;}while(*s++);}
static const unsigned commonNames[]={0x9fffac,0x9fff80,0x9fff74,0x9fff98,0x9fff8c,0xa00008,0x9ffff8,0xa00028,0xa00018,0x9fffd0,0x9fffc0,0x9fffec,0x9fffe0,0xa00048,0xa00038};
struct Table {void** vtable; unsigned id;};
static Table tables[3]; static void* vtable[10];
struct Guard {uint32_t pre[4]; SeaShader object; uint32_t post[4];};
static Guard active;
struct Event {unsigned kind,table,a,b; unsigned char snapshot[sizeof(SeaShader)];};
static Event events[4096], saved[4096]; static unsigned count, savedCount, mode, error, directCount;
static void log(unsigned kind,Table* t,unsigned a,unsigned b){if(count==4096){error=1;return;}Event& e=events[count++];e.kind=kind;e.table=t->id;e.a=a;e.b=b;memcpy(e.snapshot,&active.object,sizeof(SeaShader));}
static uint32_t handle(Table* t,unsigned h){return (mode%4==1 || (mode%4==2 && (h&1)))?0:(h ^ (t->id*0x10000001u));}
static uint32_t SEA_STD byName(Table* t,uint32_t parent,const char* name){log(1,t,parent,hash(name));if(parent)error=2;unsigned h=handle(t,hash(name));++directCount;if((mode&16)&&directCount==3)active.object.vertexConstants=(ConstantTable*)&tables[2];if((mode&32)&&directCount==5)active.object.pixelConstants=(ConstantTable*)&tables[2];if(directCount==11){if(mode&64)active.object.vertexConstants=0;if(mode&128)active.object.pixelConstants=0;}return h;}
// D3DXCONSTANTTABLE_DESC: creator, version, constants. Failure is nonzero.
static int SEA_STD describe(Table* t,uint32_t* d){log(2,t,0,0);d[0]=0;d[1]=0;d[2]=(mode&8)?0:15;return (mode&4)?-1:0;}
static uint32_t SEA_STD byIndex(Table* t,uint32_t parent,uint32_t i){log(3,t,parent,i);if(parent||i>=15)error=3;return (mode%4==3 && i%3==0)?0:i+1;}
static int SEA_STD describeConstant(Table* t,uint32_t h,uint32_t* d,uint32_t* n){log(4,t,h,*n);if(*n!=1||h<1||h>15)error=4;*n=1;d[0]=commonNames[h-1];return -1; /* original ignores descriptor status */}
static void initNames(){
putName(0x9fe740, "matWorldViewProj");
putName(0x9fe764, "matWorld");
putName(0xa0154c, "eyePositionWS");
putName(0xa0155c, "g_sunAng");
putName(0xa01538, "gTimer");
putName(0xa01540, "gBumpScale");
putName(0xa0151c, "gTextureScale");
putName(0xa00028, "g_ambientColor");
putName(0x9fffd0, "g_specularColor");
putName(0xa0152c, "gWaveScale");
putName(0xa014dc, "gBumpSpeed");
putName(0x9fffac, "g_repositionParams");
putName(0x9fff80, "gFogParams");
putName(0x9fff74, "gFogColour");
putName(0x9fff98, "gFogHeightParams");
putName(0x9fff8c, "alphaValue");
putName(0xa00008, "g_specularScale");
putName(0x9ffff8, "g_specularPower");
putName(0xa00018, "g_diffuseColor");
putName(0x9fffc0, "shadowMapPos");
putName(0x9fffec, "maskColor");
putName(0x9fffe0, "shadowColor");
putName(0xa00048, "skinMatrixArray");
putName(0xa00038, "g_morphAmounts");}
extern "C" int test_main(){
 static_assert(sizeof(SeaShader)==0xcc,"layout");
 static_assert(offsetof(SeaShader,matrix)==0x88,"matrix");
 static_assert(offsetof(ShaderManager,vertexConstants)==0x91c,"manager");
 initNames(); cookie=0x19378246;
 seh[0]=0x13572468; if(test_install_fs(seh)!=0)return 10;
 vtable[5]=(void*)describe;vtable[6]=(void*)describeConstant;vtable[8]=(void*)byIndex;vtable[9]=(void*)byName;
 for(unsigned i=0;i<3;++i){tables[i].vtable=vtable;tables[i].id=i+1;}
 static ShaderManager manager; managerFixture=&manager; seaShaderManager=&manager;
 static Guard initial,expected;
 for(unsigned c=0;c<256;++c){
  mode=c; error=0;dependencyFsError=0;seh[0]=0x13572468u^(c*0x1020304u);cookie=(c%3==0)?0:((c%3==1)?0xffffffffu:0x19378246u);
  for(unsigned i=0;i<sizeof(initial);++i)((unsigned char*)&initial)[i]=(unsigned char)(c*37+i*13);
  manager.vertexShader=(c&1)?0:0xfedcba98;manager.pixelShader=(c&2)?0xffffffff:0x12345678;
  manager.vertexConstants=(ConstantTable*)&tables[0];manager.pixelConstants=(ConstantTable*)&tables[(c/64)%2];
  memcpy(&active,&initial,sizeof(active));count=0;directCount=0;
  if(original_shader_sea_ctor(&active.object)!=&active.object)return 11;
  if(test_get_fs_head()!=seh[0])return 12;
  if(error||directCount!=11)return 13;
  memcpy(&expected,&active,sizeof(active));savedCount=count;memcpy(saved,events,count*sizeof(Event));
  memcpy(&active,&initial,sizeof(active));count=0;directCount=0;
  if(active.object.construct()!=&active.object)return 14;
  if(test_get_fs_head()!=seh[0])return 15;
  if(error||dependencyFsError||count!=savedCount||!equal(events,saved,count*sizeof(Event)))return 16;
  if(!equal(&expected,&active,sizeof(active)))return 17;
  if(!equal(active.pre,initial.pre,sizeof(active.pre))||!equal(active.post,initial.post,sizeof(active.post)))return 18;
  if(!equal(active.object.untouchedTail,initial.object.untouchedTail,3))return 19;
  if(active.object.vtable!=0xa015d0||active.object.flagC8||active.object.state58||active.object.state80||active.object.state84||active.object.reserved0c)return 20;
  for(unsigned j=0;j<16;++j)if(active.object.matrix[j]!=((j%5==0)?1.0f:0.0f))return 21;
 }
 const char message[]="PASS: 256 sea constructor differential cases, callback snapshots, guards and FS restoration\n";test_write(message,sizeof(message)-1);return 0;
}
