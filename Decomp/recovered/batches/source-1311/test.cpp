#include "impl.hpp"
using namespace riff;
extern "C" Record48* __attribute__((fastcall)) original_record48_range_copy_retain(const Record48*, const Record48*, Record48*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static_assert(sizeof(Record48)==48, "32-bit record layout");
struct Resource { RetainedHeader h; uint32_t tail[3]; };
struct Arena { uint32_t guard[4]; Record48 records[8]; Resource resources[5]; uint32_t tail[4]; };
static Arena arena;
static unsigned char initial[sizeof arena], expected[sizeof arena];
static uint32_t fs_storage[16];
static void copy(void* d,const void* s,unsigned n) { unsigned char* a=(unsigned char*)d; const unsigned char* b=(const unsigned char*)s; for(unsigned i=0;i<n;++i)a[i]=b[i]; }
static bool equal(const void* a,const void* b,unsigned n) { const unsigned char* x=(const unsigned char*)a; const unsigned char* y=(const unsigned char*)b; for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false; return true; }
// GCC fastcall supplies the right argument locations, but assumes RET 4.
// At the mandated -O0 this noinline adapter has a frame-pointer epilogue;
// that epilogue restores ESP and therefore cleans the unpopped argument.
// Inspect its generated code if the test build flags are changed.
__attribute__((noinline)) static Record48* call_original(const Record48* a,const Record48* b,Record48* d) {
    volatile Record48* result = original_record48_range_copy_retain(a,b,d);
    return const_cast<Record48*>(result);
}
extern "C" int test_main() {
    fs_storage[0]=0x12345678U;
    if(test_install_fs(fs_storage)!=0 || test_get_fs_head()!=0x12345678U) return 1;
    const uint32_t counts[]={0,1,0xfffffffeU,0xffffffffU};
    for(unsigned mask=0;mask<16;++mask) for(unsigned dup=0;dup<2;++dup)
    for(unsigned count=0;count<=3;++count) for(unsigned mode=0;mode<4;++mode)
    for(unsigned c=0;c<4;++c) {
        unsigned char* p=(unsigned char*)&arena;
        for(unsigned i=0;i<sizeof arena;++i)p[i]=(unsigned char)(i*37+mask);
        for(unsigned i=0;i<5;++i)arena.resources[i].h.references=counts[c];
        for(unsigned j=0;j<8;++j) for(unsigned i=0;i<4;++i)
            arena.records[j].retained[i]=(mask&(1U<<i))?&arena.resources[dup?0:i].h:0;
        Record48* first=&arena.records[1];
        Record48* last=first+count;
        Record48* dst= mode==0 ? &arena.records[5] : mode==1 ? first : mode==2 ? &arena.records[2] : &arena.records[0];
        copy(initial,&arena,sizeof arena);
        Record48* result=record48_range_copy_retain(first,last,dst);
        if(result!=dst+count) return 2;
        copy(expected,&arena,sizeof arena);
        copy(&arena,initial,sizeof arena);
        Record48* oracle=call_original(first,last,dst);
        if(test_get_fs_head()!=0x12345678U) return 3;
        if(oracle!=result || !equal(expected,&arena,sizeof arena)) return 4;
    }
    // Empty ranges accept arbitrary equal bounds and never touch either pointer.
    Record48* invalid=(Record48*)(uintptr_t)1;
    Record48* dest=(Record48*)(uintptr_t)0x1234;
    if(record48_range_copy_retain(invalid,invalid,dest)!=dest) return 5;
    if(call_original(invalid,invalid,dest)!=dest || test_get_fs_head()!=0x12345678U) return 6;
    // Null destination skips exactly the first element; a one-element range
    // avoids the next iteration's invalid address 0x30.
    if(record48_range_copy_retain(invalid,(Record48*)(uintptr_t)49,0)!=(Record48*)(uintptr_t)48) return 7;
    if(call_original(invalid,(Record48*)(uintptr_t)49,0)!=(Record48*)(uintptr_t)48 || test_get_fs_head()!=0x12345678U) return 8;
    test_write("record48 range differential tests passed\n",41);
    return 0;
}
