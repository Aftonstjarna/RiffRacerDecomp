#include "impl.hpp"
#include <stddef.h>
using namespace riff;
extern "C" void __attribute__((thiscall)) original_script_gc_begin_mark(State*);
extern "C" void __attribute__((thiscall)) original_script_gc_scan_roots(Global*);
extern "C" void __attribute__((fastcall)) original_script_gc_mark_object(Global*, Object*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs[32];
static unsigned badfs, calls, scans;
namespace riff {
void markObject(Global* g, Object* o) { ++calls; original_script_gc_mark_object(g,o); if (test_get_fs_head()!=fs[0]) badfs=1; }
void scanRoots(Global* g) { ++scans; original_script_gc_scan_roots(g); if (test_get_fs_head()!=fs[0]) badfs=1; }
}
struct Fixture { State state; Global g; ThreadObject thread; Object objects[12]; };
static Fixture f;
static unsigned char expected[sizeof f];
static void init(unsigned seed, int tag1, int tag2, unsigned alias) {
    unsigned char* p = reinterpret_cast<unsigned char*>(&f);
    for (unsigned i=0;i<sizeof f;++i) p[i]=(unsigned char)(i*29+seed);
    f.state.global=&f.g; f.g.main_thread=&f.thread;
    reinterpret_cast<Object*>(&f.thread)->type=11;
    reinterpret_cast<Object*>(&f.thread)->marks=(unsigned char)seed;
    for (unsigned i=0;i<12;++i) { f.objects[i].type=11; f.objects[i].marks=(unsigned char)(seed+i*13); }
    f.thread.value.tag=tag1; f.thread.value.object=alias ? reinterpret_cast<Object*>(&f.thread) : &f.objects[0];
    f.g.value.tag=tag2; f.g.value.object=alias ? f.thread.value.object : &f.objects[1];
    for (unsigned i=0;i<9;++i) f.g.roots[i]=(seed & (1u<<i)) ? &f.objects[i+2] : 0;
}
static int run(unsigned seed,int t1,int t2,unsigned alias) {
    init(seed,t1,t2,alias);
    original_script_gc_begin_mark(&f.state);
    if (test_get_fs_head()!=fs[0]) return 1;
    unsigned char* p=reinterpret_cast<unsigned char*>(&f);
    for (unsigned i=0;i<sizeof f;++i) expected[i]=p[i];
    init(seed,t1,t2,alias); calls=scans=badfs=0;
    f.state.beginMark();
    if (badfs || scans!=1 || test_get_fs_head()!=fs[0]) return 2;
    for (unsigned i=0;i<sizeof f;++i) if(p[i]!=expected[i]) return 3;
    return 0;
}
extern "C" int test_main() {
    static_assert(offsetof(State,global)==0x10,"state global");
    static_assert(offsetof(Global,phase)==0x15,"phase");
    static_assert(offsetof(Global,gray)==0x24,"gray");
    static_assert(offsetof(Global,value)==0x5c,"value");
    static_assert(offsetof(Global,main_thread)==0x64,"thread");
    static_assert(offsetof(Global,roots)==0x7c,"roots");
    static_assert(offsetof(ThreadObject,value)==0x48,"thread value");
    fs[0]=0x12345678; if(test_install_fs(fs)) return 10;
    const int tags[]={-2147483647-1,-1,0,3,4,5,2147483647};
    for(unsigned s=0;s<512;++s) for(unsigned i=0;i<7;++i) for(unsigned j=0;j<7;++j) for(unsigned a=0;a<2;++a) {
        int e=run(s,tags[i],tags[j],a); if(e) return 20+e;
    }
    // Invalid value pointers must be ignored for noncollectable signed tags.
    init(0,3,-1,0); f.thread.value.object=0; f.g.value.object=0;
    original_script_gc_begin_mark(&f.state); if(test_get_fs_head()!=fs[0]) return 30;
    init(0,3,-1,0); f.thread.value.object=0; f.g.value.object=0;
    calls=scans=badfs=0; f.state.beginMark(); if(badfs || scans!=1) return 31;
    return 0;
}
