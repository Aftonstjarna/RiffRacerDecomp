#include "impl.hpp"
using namespace recovered;
extern "C" const char* __attribute__((thiscall)) original_convex_hull_shape_serialize(ConvexHullShape*, HullData*, Serializer*);
static ConvexHullShape shape, initial, afterOriginal;
static HullData destination, originalDestination;
static uint32_t points[32], alternate[32], storage[40], originalStorage[40];
static unsigned mode, failure;
static bool textEqual(const char* a,const char* b) { while(*a && *a==*b){++a;++b;} return *a==*b; }
static bool equal(const void* a,const void* b,unsigned n) {
 const unsigned char* x=static_cast<const unsigned char*>(a); const unsigned char* y=static_cast<const unsigned char*>(b);
 for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
 return true;
}
struct Probe : Serializer {
 unsigned stage; Chunk chunk;
 void RR_THISCALL slot0() {} void RR_THISCALL slot1() {} void RR_THISCALL slot2() {}
 void RR_THISCALL slot5() {} void RR_THISCALL slot7() {} void RR_THISCALL slot8() {} void RR_THISCALL slot10() {}
 const char* RR_THISCALL findNameForPointer(const void* p) {
  if(stage!=0 || p!=&shape) failure=1;
  stage=1; return (mode&1)?"hull":0;
 }
 uint32_t RR_THISCALL getUniquePointer(const void* p) {
  if(stage==1) {
   if(p!=((mode&1)?static_cast<const void*>("hull"):0)) failure=2;
   stage=2; return (mode&2)?0:0xabc01234u;
  }
  if(stage!=((mode&2)?2u:3u) || p!=initial.points || destination.count!=initial.pointCount) failure=3;
  stage=4;
  if(mode&4) {shape.pointCount=7; shape.points=alternate;}
  return (mode&8)?0:0xfedc1234u;
 }
 void RR_THISCALL serializeName(const char* p) {
  if(stage!=2 || p!=((mode&1)?static_cast<const void*>("hull"):0) || destination.base.vtable!=0xabc01234u) failure=4;
  stage=3;
 }
 Chunk* RR_THISCALL allocate(uint32_t size,int32_t count) {
  if(stage!=4 || size!=16 || count!=initial.pointCount || destination.doublePoints!=0 || destination.points!=((mode&8)?0:0xfedc1234u)) failure=5;
  stage=5; chunk.header[0]=0x11111111; chunk.header[1]=0x22222222; chunk.data=storage+4;
  if(mode&16) shape.points=alternate;
  return &chunk;
 }
 void RR_THISCALL finalize(Chunk* c,const char* type,uint32_t code,const void* old) {
  if(stage!=5 || c!=&chunk || code!=0x59415241u || old!=shape.points) failure=6;
  // Original read-only strings are unmapped in the test ELF; check their VA.
  if(reinterpret_cast<uintptr_t>(type)!=0x9fb0f8u && !textEqual(type,"btVector3FloatData")) failure=7;
  if(chunk.header[0]!=0x11111111 || chunk.header[1]!=0x22222222) failure=8;
  stage=6;
 }
};
static void reset(Probe& probe) {
 shape=initial;
 unsigned char* d=reinterpret_cast<unsigned char*>(&destination);
 for(unsigned i=0;i<sizeof(destination);++i)d[i]=static_cast<unsigned char>(0xa0+i);
 for(unsigned i=0;i<40;++i)storage[i]=0xdedededeu;
 probe.stage=0; failure=0;
}
extern "C" int test_main() {
 Probe probe;
 const int32_t counts[]={0,1,2,8,-1,static_cast<int32_t>(0x80000000u)};
 for(mode=0;mode<64;++mode)for(unsigned k=0;k<6;++k) {
  unsigned char* s=reinterpret_cast<unsigned char*>(&initial);
  for(unsigned i=0;i<sizeof(initial);++i)s[i]=static_cast<unsigned char>(mode*7+i*13);
  initial.pointCount=counts[k]; initial.pointCapacity=0xfedcba98; initial.points=((mode&32) && counts[k]<=0)?0:points;
  for(unsigned i=0;i<32;++i){points[i]=0x7f800001u+i*0x1020304u; alternate[i]=0x80000000u+i*0xabcdefu;}
  reset(probe); const char* a=original_convex_hull_shape_serialize(&shape,&destination,&probe);
  if(failure || reinterpret_cast<uintptr_t>(a)!=0x9fb10cu)return 10+failure;
  unsigned calls=probe.stage;
  if(calls!=(counts[k]?6u:((mode&2)?2u:3u)))return 20;
  originalDestination=destination; afterOriginal=shape;
  for(unsigned i=0;i<40;++i)originalStorage[i]=storage[i];
  reset(probe); const char* b=shape.serialize(&destination,&probe);
  if(failure || !textEqual(b,"btConvexHullShapeData"))return 30+failure;
  if(probe.stage!=calls || !equal(&destination,&originalDestination,sizeof(destination)) || !equal(&shape,&afterOriginal,sizeof(shape)) || !equal(storage,originalStorage,sizeof(storage)))return 40;
  if(destination.base.untouched08!=0xabaaa9a8u || destination.base.untouched30!=0xd3d2d1d0u)return 41;
  if(!counts[k] && destination.points!=0)return 42;
  if(destination.count!=counts[k] || destination.doublePoints!=0)return 43;
  unsigned used=counts[k]>0?static_cast<unsigned>(counts[k])*4:0;
  for(unsigned i=0;i<40;++i) if((i<4 || i>=4+used) && storage[i]!=0xdedededeu)return 44;
  for(unsigned i=0;i<32;++i) if(points[i]!=0x7f800001u+i*0x1020304u || alternate[i]!=0x80000000u+i*0xabcdefu)return 45;
 }
 return 0;
}
