#include "impl.hpp"
// regparm(3) maps dummy -> EAX, end -> EDX, begin -> ECX, leaving
// destination on the caller-cleaned stack. This models the observed custom
// ABI, which is neither standard thiscall nor callee-cleaned fastcall.
extern "C" void* original_record12_copy_range(uintptr_t dummy, const void* end,
    const void* begin, void* destination) __attribute__((regparm(3)));
extern "C" void test_write(const char*, unsigned);
static unsigned char recovered[256], oracle[256];
static void initialize() {
    for (unsigned i=0;i<256;++i) recovered[i]=oracle[i]=static_cast<unsigned char>((i*73u+19u) ^ (i>>1));
}
static bool run(unsigned source, unsigned dest, unsigned count) {
    initialize();
    void* a=record12_copy_range(recovered+source,recovered+source+12*count,recovered+dest);
    void* b=original_record12_copy_range(0,oracle+source+12*count,oracle+source,oracle+dest);
    if (a!=recovered+dest+12*count || b!=oracle+dest+12*count) return false;
    // Entire buffers include guards, unmodified source and unrelated bytes.
    for (unsigned i=0;i<256;++i) if(recovered[i]!=oracle[i]) return false;
    return true;
}
extern "C" int test_main() {
    for(unsigned n=0;n<=8;++n) {
        if(!run(8,144,n)) return 1;
        if(!run(32,32,n)) return 2;
    }
    for(unsigned offset=1;offset<=25;++offset) {
        if(!run(48,48+offset,6)) return 3;
        if(!run(48,48-offset,6)) return 4;
    }
    // Empty bounds are never dereferenced. A single null-destination step
    // also never reads its source, but returns address 12. Multiple such
    // steps would attempt a write at address 12 and are intentionally excluded.
    const void* p=reinterpret_cast<const void*>(static_cast<uintptr_t>(0x1000));
    const void* q=reinterpret_cast<const void*>(static_cast<uintptr_t>(0x100c));
    if(record12_copy_range(p,p,0)!=0 || original_record12_copy_range(0,p,p,0)!=0) return 5;
    if(reinterpret_cast<uintptr_t>(record12_copy_range(p,q,0))!=12 ||
       reinterpret_cast<uintptr_t>(original_record12_copy_range(0,q,p,0))!=12) return 6;
    if(record12_copy_range(0,0,0)!=0 || original_record12_copy_range(0,0,0,0)!=0) return 7;
    test_write("record12-copy-range: passed\n",28);
    return 0;
}
