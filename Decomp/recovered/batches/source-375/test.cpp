#include "impl.hpp"
// GCC regparm(3), cdecl cleanup: unused EAX, end EDX, first ECX,
// destination on stack. This describes the original custom ABI without asm.
extern "C" unsigned char* original_record24_range_copy(uintptr_t unused_eax,
    const void* end, const void* first, void* destination) __attribute__((regparm(3)));
static unsigned char a[512], b[512];
static void fill(unsigned seed) {
    for(unsigned i=0;i<512;++i) a[i]=b[i]=static_cast<unsigned char>((i*73u+seed)^(i>>2));
}
static int compare(unsigned src,unsigned dst,unsigned count,unsigned seed) {
    fill(seed);
    unsigned char* expected=original_record24_range_copy(0,b+src+24*count,b+src,b+dst);
    unsigned char* actual=record24_range_copy(a+src,a+src+24*count,a+dst);
    if(actual!=a+dst+24*count || expected!=b+dst+24*count) return 1;
    // Entire arenas include source, destination, prefix/suffix canaries.
    for(unsigned i=0;i<512;++i) if(a[i]!=b[i]) return 2;
    return 0;
}
extern "C" int test_main() {
    for(unsigned count=0;count<=8;++count) {
        if(compare(17,273,count,41+count)) return 1;
        if(compare(273,17,count,91+count)) return 2;
        if(compare(33,33,count,11+count)) return 3;
    }
    // Overlap within each SIMD chunk, across the 16/8 boundary and records.
    for(unsigned delta=1;delta<=31;++delta) {
        if(compare(100,100+delta,6,delta)) return 4;
        if(compare(100+delta,100,6,delta+53)) return 5;
    }
    // Null destination only skips the CURRENT record; two records would
    // attempt a write at address 24 and are outside this normal-path test.
    void* fake=reinterpret_cast<void*>(static_cast<uintptr_t>(0x12345));
    void* next=reinterpret_cast<void*>(static_cast<uintptr_t>(0x12345+24));
    if(original_record24_range_copy(0,next,fake,0)!=reinterpret_cast<void*>(24)) return 6;
    if(record24_range_copy(fake,next,0)!=reinterpret_cast<void*>(24)) return 7;
    if(original_record24_range_copy(0,fake,fake,0)!=0) return 8;
    if(record24_range_copy(fake,fake,0)!=0) return 9;
    return 0;
}
