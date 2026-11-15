#include "impl.hpp"
// regparm(3) passes ignored EAX, end EDX, begin ECX, then destination
// on the caller-cleaned stack. This is a test-only custom-ABI bridge;
// ordinary fastcall would incorrectly assume callee stack cleanup.
extern "C" void* __attribute__((regparm(3))) original_record32_copy_construct_range(
    unsigned ignored_eax, const void* end, const void* begin, void* destination);
static unsigned char actual[512], expected[512];
static void initialize(unsigned seed) {
    for (unsigned i=0;i<512;++i) actual[i]=expected[i]=static_cast<unsigned char>((i*73+seed)^(i>>2));
}
static int compare(unsigned src, unsigned dst, unsigned count, unsigned seed) {
    initialize(seed);
    void* a=record32_copy_construct_range(actual+src,actual+src+32*count,actual+dst);
    void* b=original_record32_copy_construct_range(0,expected+src+32*count,expected+src,expected+dst);
    if (a!=actual+dst+32*count || b!=expected+dst+32*count) return 1;
    for(unsigned i=0;i<512;++i) if(actual[i]!=expected[i]) return 2;
    return 0;
}
extern "C" int test_main() {
    // Whole-buffer equality checks both writes and untouched source/guards.
    for(unsigned seed=0;seed<5;++seed) {
        for(unsigned n=0;n<=6;++n) {
            if(compare(17,277,n,seed)) return 1;
            if(compare(33,33,n,seed)) return 2;
        }
        // Unaligned forward and backward overlap, including intra-word offsets.
        for(unsigned delta=1;delta<=36;++delta) {
            if(compare(81,81+delta,5,seed)) return 3;
            if(compare(81,81-delta,5,seed)) return 4;
        }
    }
    if(record32_copy_construct_range(0,0,0)!=0) return 5;
    if(original_record32_copy_construct_range(0,0,0,0)!=0) return 6;
    initialize(9);
    if(record32_copy_construct_range(actual+1,actual+33,0)!=reinterpret_cast<void*>(32)) return 7;
    if(original_record32_copy_construct_range(0,expected+33,expected+1,0)!=reinterpret_cast<void*>(32)) return 8;
    for(unsigned i=0;i<512;++i) if(actual[i]!=expected[i]) return 9;
    return 0;
}
