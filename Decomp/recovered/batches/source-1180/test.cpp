#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_script_gc_shrink_buffers(ScriptState*);
extern "C" void __attribute__((fastcall)) original_script_string_buckets_resize(ScriptState*,int32_t);
extern "C" void* __attribute__((regparm(3))) original_script_reallocate(unsigned,void*,ScriptState*,uint32_t,uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
extern "C" void* memset(void* p,int c,unsigned n) { unsigned char* q=(unsigned char*)p; while(n--) *q++=(unsigned char)c; return p; }
extern "C" void* memcpy(void* d,const void* s,unsigned n) { unsigned char* a=(unsigned char*)d; const unsigned char* b=(const unsigned char*)s; while(n--) *a++=*b++; return d; }
struct Node { Node* next; unsigned char x[4]; uint32_t hash,length; };
struct Fixture { ScriptState state; unsigned char stateTail[80]; ScriptGlobal g; unsigned char globalTail[64]; void* oldBuckets[128]; void* newBuckets[128]; Node nodes[8]; unsigned char oldBuffer[128],newBuffer[128]; };
static Fixture f;
struct Event {void* ptr; uint32_t oldSize,newSize;};
static Event events[4]; static unsigned calls, bad;
static void* allocator(void* data,void* ptr,uint32_t oldSize,uint32_t newSize) {
    if(data!=&f || calls>=4) {bad=1;return 0;}
    events[calls].ptr=ptr; events[calls].oldSize=oldSize; events[calls].newSize=newSize; ++calls;
    if (!ptr && newSize) return f.newBuckets;
    if (ptr==f.oldBuckets && !newSize) return 0;
    if (ptr==f.oldBuffer && newSize) return f.newBuffer;
    bad=2; return 0;
}
static void resizeAdapter(ScriptState* s,int32_t n) { original_script_string_buckets_resize(s,n); if(test_get_fs_head()!=0xffffffffu) bad=3; }
static void* reallocAdapter(ScriptState* s,void* p,uint32_t a,uint32_t b) { void* r=original_script_reallocate(0,p,s,a,b); if(test_get_fs_head()!=0xffffffffu) bad=4; return r; }
static const ScriptServices services={resizeAdapter,reallocAdapter};
static bool equal(const void* a,const void* b,unsigned n) {const unsigned char* x=(const unsigned char*)a; const unsigned char* y=(const unsigned char*)b; while(n--) if(*x++!=*y++) return false; return true;}
static void setup(int32_t count,uint32_t used,uint32_t size,unsigned gc) {
    memset(&f,0x5a,sizeof f); memset(events,0,sizeof events); calls=bad=0;
    f.state.global=&f.g; f.g.buckets=f.oldBuckets; f.g.used=used; f.g.bucketCount=count;
    f.g.allocator=allocator; f.g.allocatorData=&f; ((unsigned char*)&f.g)[21]=(unsigned char)gc;
    *(uint32_t*)((unsigned char*)&f.g+68)=0x12345678u;
    f.g.buffer=f.oldBuffer; f.g.bufferSize=size;
    memset(f.oldBuckets,0,sizeof f.oldBuckets);
    for(unsigned i=0;i<8;++i) {f.nodes[i].hash=i*17; f.nodes[i].next=(Node*)f.oldBuckets[i]; f.oldBuckets[i]=&f.nodes[i];}
}
struct Snapshot { Fixture f; Event e[4]; unsigned count; };
static void capture(Snapshot& s) {memcpy(&s.f,&f,sizeof f);memcpy(s.e,events,sizeof events);s.count=calls;}
static int run(int32_t count,uint32_t used,uint32_t size,unsigned gc) {
    setup(count,used,size,gc); original_script_gc_shrink_buffers(&f.state);
    if(test_get_fs_head()!=0xffffffffu || bad) return 1;
    Snapshot expected; capture(expected);
    setup(count,used,size,gc); f.state.shrinkBuffers(services);
    Snapshot actual; capture(actual);
    if(bad || test_get_fs_head()!=0xffffffffu || !equal(&expected,&actual,sizeof expected)) return 2;
    unsigned resize=(count>64 && used<(uint32_t)(count/4) && gc!=2);
    if(calls!=resize*2+(size>64)) return 3;
    if(f.g.bufferSize!=(size>64?size/2:size)) return 4;
    if(f.g.buffer!=(size>64?(void*)f.newBuffer:(void*)f.oldBuffer)) return 5;
    return 0;
}
extern "C" int test_main() {
    static unsigned fs[8]; fs[0]=0xffffffffu; if(test_install_fs(fs)) return 10;
    const int32_t counts[]={-1,0,63,64,65,66,127,128};
    const uint32_t used[]={0,15,16,17,31,32,0xffffffffu};
    const uint32_t sizes[]={0,63,64,65,66,127,128,0x80000000u,0xffffffffu};
    for(unsigned i=0;i<8;++i) for(unsigned j=0;j<7;++j) for(unsigned k=0;k<9;++k) for(unsigned g=0;g<2;++g) {
        int r=run(counts[i],used[j],sizes[k],g?2:0); if(r) return 10+r;
    }
    test_write("PASS\n",5); return 0;
}
