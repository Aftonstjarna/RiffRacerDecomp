#include "impl.hpp"
// GCC regparm(3) maps arguments to EAX, EDX, ECX, then caller-cleaned
// stack. EAX is unused on entry, so the dummy exposes the original custom
// register ABI exactly, without a fastcall callee-pop mismatch.
extern "C" uintptr_t original_record513_range_copy(uintptr_t unused_eax,
    const riff::Record513* last, const riff::Record513* first,
    uintptr_t destination) __attribute__((regparm(3)));
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs_storage[16];
static riff::Record513 source[9];
static unsigned char before[sizeof(source)];
static unsigned char actual[sizeof(source)+32], expected[sizeof(source)+32];
static bool source_unchanged() {
    const unsigned char* p = reinterpret_cast<const unsigned char*>(source);
    for (unsigned i=0; i<sizeof(source); ++i) if(p[i]!=before[i]) return false;
    return true;
}
extern "C" int test_main() {
    fs_storage[0]=0x12345678;
    if(test_install_fs(fs_storage)!=0) return 1;
    unsigned char* p=reinterpret_cast<unsigned char*>(source);
    for(unsigned i=0;i<sizeof(source);++i) before[i]=p[i]=static_cast<unsigned char>((i*73u)^(i>>3));
    for(unsigned start=0;start<4;++start) for(unsigned count=0;count<=5;++count)
    for(unsigned offset=0;offset<4;++offset) {
        for(unsigned i=0;i<sizeof(actual);++i) actual[i]=expected[i]=0xa7;
        uintptr_t a=riff::copy_record513_range(source+start,source+start+count,
                                            reinterpret_cast<uintptr_t>(actual+8+offset));
        uintptr_t b=original_record513_range_copy(0,source+start+count,source+start,
                                            reinterpret_cast<uintptr_t>(expected+8+offset));
        if(test_get_fs_head()!=fs_storage[0]) return 2;
        if(a!=reinterpret_cast<uintptr_t>(actual+8+offset)+513*count ||
           b!=reinterpret_cast<uintptr_t>(expected+8+offset)+513*count) return 3;
        for(unsigned i=0;i<sizeof(actual);++i) {
            if(actual[i]!=expected[i]) return 4;
            unsigned begin=8+offset, end=begin+513*count;
            unsigned char wanted=(i>=begin && i<end)? before[start*513+i-begin]:0xa7;
            if(actual[i]!=wanted) return 5;
        }
        if(!source_unchanged()) return 6;
    }
    // Single null destination skips memory access and returns 513. Multiple
    // records with null destination would next write address 513: invalid here.
    for(unsigned count=0;count<2;++count) {
        uintptr_t a=riff::copy_record513_range(source,source+count,0);
        uintptr_t b=original_record513_range_copy(0,source+count,source,0);
        if(test_get_fs_head()!=fs_storage[0] || a!=b || a!=513*count) return 7;
    }
    // Empty range never dereferences either argument, even null source.
    if(riff::copy_record513_range(0,0,17)!=17 ||
       original_record513_range_copy(0,0,0,17)!=17) return 8;
    if(test_get_fs_head()!=fs_storage[0] || !source_unchanged()) return 9;
    return 0;
}
