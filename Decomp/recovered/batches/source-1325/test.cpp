#include "impl.hpp"
// The callee uses ECX, EDX and a caller-cleaned third argument. GCC's
// fastcall declaration sets up these registers; isolate each call in a
// frame-pointer function because GCC expects the callee to pop that argument.
extern "C" void* __attribute__((fastcall)) original_worker_record64_range_construct(const void*, const void*, void*);
__attribute__((noinline)) static uintptr_t oracle(const void* a, const void* b, void* c) {
    return reinterpret_cast<uintptr_t>(original_worker_record64_range_construct(a,b,c));
}
static unsigned char x[640], y[640];
extern "C" int test_main() {
    for (unsigned n=0;n<=3;++n) for (unsigned src=128;src<=160;src+=7)
    for (unsigned dst=64;dst<=300;dst+=1) {
        if (src+n*64>640 || dst+n*64>640) return 1;
        for(unsigned i=0;i<640;++i) x[i]=y[i]=static_cast<unsigned char>(i*37+n*19+dst);
        uintptr_t a=oracle(x+src,x+src+n*64,x+dst);
        uintptr_t b=reinterpret_cast<uintptr_t>(worker_record64_range_construct(y+src,y+src+n*64,y+dst));
        if (a-reinterpret_cast<uintptr_t>(x)!=b-reinterpret_cast<uintptr_t>(y)) return 2;
        for(unsigned i=0;i<640;++i) if(x[i]!=y[i]) return 3;
    }
    // A null destination is skipped for the first record, then advanced.
    // Only one record is safe without mapping address 64.
    if (oracle(x,x+64,0)!=64 || reinterpret_cast<uintptr_t>(worker_record64_range_construct(y,y+64,0))!=64) return 4;
    if (oracle(x,x,0)!=0 || worker_record64_range_construct(y,y,0)!=0) return 5;
    return 0;
}
