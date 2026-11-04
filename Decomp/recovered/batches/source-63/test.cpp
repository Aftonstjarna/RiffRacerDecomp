#include "impl.hpp"
using namespace riff;
extern "C" int32_t __attribute__((thiscall)) original_buffer_allocate(Buffer*, Device*, uint32_t, uint32_t, uint32_t);
extern "C" void test_write(const char*, unsigned);
extern "C" void* memset(void* p, int c, unsigned n) { unsigned char* q=(unsigned char*)p; while(n--) *q++=(unsigned char)c; return p; }
extern "C" void* memcpy(void* p,const void* s,unsigned n) { unsigned char* q=(unsigned char*)p; const unsigned char* r=(const unsigned char*)s; while(n--) *q++=*r++; return p; }
static Buffer b;
static Device dev, oldDev;
static Resource vertex, index, oldVertex, oldIndex;
static int32_t firstResult, secondResult;
static uint32_t flagValue, bytesValue, countValue;
static bool writeFirst, writeSecond;
static unsigned errors, sequence;
static void check(bool ok) { if(!ok) ++errors; }
static void unchangedTail() {
 check(b.vertexCursor==0x12345678 && b.indexCursor==0x87654321);
 check(b.vertexBytes==0x13579bdf && b.indexCount==0x2468ace0);
}
static uint32_t RIFF_STDCALL release(Resource* p) {
 check(sequence++==2); check(p==&vertex); check(b.vertexBuffer==&vertex);
 check(b.device==&oldDev); unchangedTail(); return 0xdeadbeef;
}
static uint32_t RIFF_STDCALL addref(Device* p) {
 check(sequence++==2); check(p==&dev); check(b.device==&dev);
 check(b.vertexBuffer==(writeFirst?&vertex:&oldVertex));
 check(b.indexBuffer==(writeSecond?&index:&oldIndex)); unchangedTail(); return 999;
}
static int32_t RIFF_STDCALL createVertex(Device* p,uint32_t size,uint32_t usage,uint32_t fvf,uint32_t pool,Resource** out,void* shared) {
 check(sequence++==0); check(p==&dev); check(size==bytesValue);
 check(usage==((flagValue&255)?0x248u:0x228u)); check(!fvf && !pool && !shared);
 check(out==&b.vertexBuffer); check(b.device==&oldDev); unchangedTail();
 if(writeFirst) *out=&vertex;
 return firstResult;
}
static int32_t RIFF_STDCALL createIndex(Device* p,uint32_t size,uint32_t usage,uint32_t format,uint32_t pool,Resource** out,void* shared) {
 check(sequence++==1); check(p==&dev); check(size==(countValue<<2));
 check(usage==((flagValue&255)?0x248u:0x228u)); check(format==102 && !pool && !shared);
 check(out==&b.indexBuffer); check(b.device==&oldDev); unchangedTail();
 if(writeSecond) *out=&index;
 return secondResult;
}
static DeviceVTable dv;
static ResourceVTable rv;
static void run(bool original) {
 b.device=&oldDev; b.vertexBuffer=&oldVertex; b.indexBuffer=&oldIndex;
 b.vertexCursor=0x12345678; b.indexCursor=0x87654321;
 b.vertexBytes=0x13579bdf; b.indexCount=0x2468ace0; sequence=0;
 int32_t r=original?original_buffer_allocate(&b,&dev,flagValue,bytesValue,countValue):b.allocate(&dev,(uint8_t)flagValue,bytesValue,countValue);
 const int32_t expected=firstResult<0?firstResult:(secondResult<0?secondResult:0);
 check(r==expected);
 if(firstResult<0) {
  check(sequence==1); check(b.device==&oldDev);
  check(b.vertexBuffer==(writeFirst?&vertex:&oldVertex)); check(b.indexBuffer==&oldIndex); unchangedTail();
 } else if(secondResult<0) {
  check(sequence==3); check(!b.vertexBuffer); check(b.device==&oldDev);
  check(b.indexBuffer==(writeSecond?&index:&oldIndex)); unchangedTail();
 } else {
  check(sequence==3); check(b.device==&dev);
  check(b.vertexBuffer==(writeFirst?&vertex:&oldVertex)); check(b.indexBuffer==(writeSecond?&index:&oldIndex));
  check(!b.vertexCursor && !b.indexCursor); check(b.vertexBytes==bytesValue && b.indexCount==countValue);
 }
}
extern "C" int test_main() {
 static_assert(sizeof(Buffer)==28,"original layout");
 dv.addRef=addref; dv.createVertexBuffer=createVertex; dv.createIndexBuffer=createIndex;
 rv.release=release; dev.vtable=&dv; vertex.vtable=&rv;
 const uint32_t flags[]={0,1,2,255,256,0xffffff00u,0xffffffffu};
 const uint32_t sizes[]={0,1,0x1000000,0xffffffffu};
 const uint32_t counts[]={0,1,0x60000,0x3fffffff,0x40000000,0x80000001,0xffffffffu};
 const int32_t results[]={0,1,0x7fffffff,(-2147483647-1),-1};
 for(unsigned f=0;f<7;++f) for(unsigned s=0;s<4;++s) for(unsigned c=0;c<7;++c)
 for(unsigned a=0;a<5;++a) for(unsigned z=0;z<5;++z) for(unsigned w=0;w<4;++w) {
  flagValue=flags[f]; bytesValue=sizes[s]; countValue=counts[c]; firstResult=results[a]; secondResult=results[z];
  writeFirst=(w&1)!=0; writeSecond=(w&2)!=0;
  // Second-call failure requires a valid releasable first buffer. A successful
  // API that leaves this pointer untouched is outside D3D's contract, but is
  // still tested on the all-success path and on first-call failures.
  if(firstResult>=0 && secondResult<0 && !writeFirst) continue;
  run(true); run(false);
 }
 if(errors) { test_write("FAIL\n",5); return 1; }
 test_write("PASS buffer-allocate\n",21); return 0;
}
