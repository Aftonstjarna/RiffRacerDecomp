#include "impl.hpp"
// regparm(3) models the private caller-cleaned ABI without an assembly shim:
// dummy EAX is ignored; end goes in EDX, begin in ECX, destination on stack.
// Neither standard fastcall (callee cleanup) nor thiscall describes this routine.
extern "C" uintptr_t original_record36_copy_range(unsigned dummy, const void* end,
    const void* begin, void* destination) __attribute__((regparm(3)));
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs_storage[8];
static unsigned char actual[640], expected[640];
static int run(unsigned source, unsigned dest, unsigned count) {
    for (unsigned i=0;i<640;++i) actual[i]=expected[i]=static_cast<unsigned char>((i*73u + i/7u + count*11u)^0xa5u);
    uintptr_t a=riff::copy_record36_range(actual+source,actual+source+count*36,actual+dest);
    uintptr_t b=original_record36_copy_range(0,expected+source+count*36,expected+source,expected+dest);
    if(test_get_fs_head()!=fs_storage[0]) return 1;
    if(a-reinterpret_cast<uintptr_t>(actual)!=b-reinterpret_cast<uintptr_t>(expected)) return 2;
    for(unsigned i=0;i<640;++i) if(actual[i]!=expected[i]) return 3;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0x13579bdfu;
    if(test_install_fs(fs_storage)!=0) return 1;
    for(unsigned count=0;count<=8;++count) {
        for(unsigned alignment=0;alignment<16;++alignment)
            if(run(32+alignment,320+((alignment+3)%16),count)) return 2;
    }
    // Forward and backward partial overlap, including within each SIMD chunk.
    for(unsigned shift=0;shift<=40;++shift) {
        if(run(100,100+shift,6)) return 3;
        if(run(100+shift,100,6)) return 4;
    }
    // An empty range performs no accesses, even with null pointers.
    if(riff::copy_record36_range(0,0,0)!=original_record36_copy_range(0,0,0,0)) return 5;
    if(test_get_fs_head()!=fs_storage[0]) return 6;
    // Null output skips precisely one record; source need not be readable.
    const void* begin=reinterpret_cast<const void*>(uintptr_t(0x1000));
    const void* end=reinterpret_cast<const void*>(uintptr_t(0x1024));
    if(riff::copy_record36_range(begin,end,0)!=36) return 7;
    if(original_record36_copy_range(0,end,begin,0)!=36) return 8;
    if(test_get_fs_head()!=fs_storage[0]) return 9;
    return 0;
}
