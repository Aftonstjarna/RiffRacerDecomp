#include "impl.hpp"
#include <stddef.h>
using namespace riff;
extern "C" void __attribute__((thiscall)) original_script_gc_scan_linked_values(Global*);
extern "C" void __attribute__((fastcall)) original_script_gc_mark_object(Global*, GCObject*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs[32];
static unsigned calls, badfs;
namespace riff { void markObject(Global* g, GCObject* o) { ++calls; original_script_gc_mark_object(g,o); if(test_get_fs_head()!=fs[0]) badfs=1; } }
struct Fixture { Global g; LinkedValue n[4]; Value v[4]; GCObject o[4]; };
static Fixture f;
static unsigned char expected[sizeof f];
static void init(unsigned seed, unsigned count, bool alias) {
    unsigned char* p=(unsigned char*)&f;
    for(unsigned i=0;i<sizeof f;++i) p[i]=(unsigned char)(i*29+seed);
    f.g.sentinel.next=count ? &f.n[0] : &f.g.sentinel;
    for(unsigned i=0;i<count;++i) {
        f.n[i].next=(i+1<count)?&f.n[i+1]:&f.g.sentinel;
        f.n[i].marked=(unsigned char)(seed >> (i*2));
        f.n[i].value=&f.v[i];
        f.v[i].tag=(int32_t)((seed+i)%8)-2;
        f.v[i].object=&f.o[alias?0:i];
        f.o[i].type=11; // outside the marker's external jump table
        f.o[i].marked=(unsigned char)(seed*17+i);
    }
}
static int run(unsigned seed,unsigned count,bool alias) {
    init(seed,count,alias);
    original_script_gc_scan_linked_values(&f.g);
    if(test_get_fs_head()!=fs[0]) return 1;
    unsigned char* p=(unsigned char*)&f;
    for(unsigned i=0;i<sizeof f;++i) expected[i]=p[i];
    init(seed,count,alias);
    calls=0; badfs=0;
    f.g.scanLinkedValues();
    if(badfs || test_get_fs_head()!=fs[0]) return 2;
    for(unsigned i=0;i<sizeof f;++i) if(p[i]!=expected[i]) return 3;
    return 0;
}
extern "C" int test_main() {
    static_assert(offsetof(Global,sentinel)==0x68,"sentinel");
    static_assert(offsetof(LinkedValue,next)==0x10,"next");
    static_assert(offsetof(LinkedValue,value)==8,"value");
    fs[0]=0x12345678; if(test_install_fs(fs)) return 10;
    for(unsigned count=0;count<=4;++count)
        for(unsigned seed=0;seed<1024;++seed)
            for(unsigned alias=0;alias<2;++alias) { int e=run(seed,count,alias!=0); if(e) return 20+e; }
    // Explicitly exercise the boundary tag and actual marker delegation.
    init(0,1,false); f.n[0].marked=0; f.v[0].tag=4;
    f.o[0].marked=0xa3; f.o[0].type=11;
    original_script_gc_scan_linked_values(&f.g);
    if(test_get_fs_head()!=fs[0] || f.o[0].marked!=0xa0) return 32;
    init(0,1,false); f.n[0].marked=0; f.v[0].tag=4;
    f.o[0].marked=0xa3; f.o[0].type=11; calls=0;
    f.g.scanLinkedValues(); if(calls!=1 || f.o[0].marked!=0xa0 || badfs) return 33;
    // Invalid pointers are safe only when short circuiting prevents access.
    init(0,1,false); f.n[0].marked=7; f.n[0].value=0;
    original_script_gc_scan_linked_values(&f.g); if(test_get_fs_head()!=fs[0]) return 30;
    f.g.scanLinkedValues();
    f.n[0].marked=0; f.n[0].value=&f.v[0]; f.v[0].tag=-2147483647-1; f.v[0].object=0;
    original_script_gc_scan_linked_values(&f.g); if(test_get_fs_head()!=fs[0]) return 31;
    f.g.scanLinkedValues();
    return 0;
}
