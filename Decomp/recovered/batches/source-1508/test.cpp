#include "impl.hpp"
#include <stddef.h>
extern "C" WorkerString* original_worker_empty_string_construct(WorkerString*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
struct Fixture { uint32_t before[3]; WorkerString s; uint32_t after[3]; };
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x = static_cast<const unsigned char*>(a);
    const unsigned char* y = static_cast<const unsigned char*>(b);
    for (unsigned i=0;i<n;++i) if (x[i]!=y[i]) return false;
    return true;
}
extern "C" int test_main() {
    static_assert(sizeof(WorkerString)==24, "layout");
    static_assert(offsetof(WorkerString,length)==16, "length");
    static_assert(offsetof(WorkerString,capacity)==20, "capacity");
    static uint32_t fs[16]; fs[0]=0x12345678;
    if (test_install_fs(fs)!=0 || test_get_fs_head()!=fs[0]) return 1;
    const uint32_t caps[]={0,15,16,0xffffffffu,0x87654321u};
    for(unsigned pattern=0;pattern<256;++pattern) for(unsigned c=0;c<5;++c) {
        Fixture a,b,expected;
        unsigned char* p=reinterpret_cast<unsigned char*>(&a);
        for(unsigned i=0;i<sizeof a;++i) p[i]=static_cast<unsigned char>(pattern+i*37);
        a.s.capacity=caps[c]; a.s.length=0xffffffffu-pattern;
        b=a; expected=a;
        expected.s.capacity=15; expected.s.length=0; expected.s.inline_storage[0]=0;
        if(worker_empty_string_construct(&a.s)!=&a.s) return 2;
        if(original_worker_empty_string_construct(&b.s)!=&b.s) return 3;
        if(test_get_fs_head()!=fs[0]) return 4;
        if(!equal(&a,&expected,sizeof a) || !equal(&b,&expected,sizeof b)) return 5;
    }
    const char msg[]="worker empty string checks passed\n";
    test_write(msg,sizeof msg-1);
    return 0;
}
