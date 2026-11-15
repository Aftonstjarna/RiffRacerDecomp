#include "impl.hpp"
using riff::RetainedObject;
// The original has fastcall register placement but cdecl stack cleanup.
// GCC cannot spell that combination. A dedicated frame-based adapter makes
// exactly one call: its frame epilogue discards the unpopped argument. No
// other calls or ESP-relative accesses follow it. Verify this adapter's
// generated code when changing toolchains. This is test-only, not port ABI.
extern "C" void __attribute__((fastcall)) original_pointer_slot_range_copy_retain(
    RetainedObject* const*, RetainedObject* const*, RetainedObject**);
static void __attribute__((noinline,optimize("O0"))) oracle(
    RetainedObject* const* b, RetainedObject* const* e, RetainedObject** d) {
    original_pointer_slot_range_copy_retain(b,e,d);
}
static int run(unsigned length, unsigned mode, uint32_t count) {
    RetainedObject a[3] = {{0x12345678,count},{0xabcdef01,17},{0x76543210,42}};
    RetainedObject b[3] = {{0x12345678,count},{0xabcdef01,17},{0x76543210,42}};
    RetainedObject* x[9]; RetainedObject* y[9];
    for (unsigned i=0;i<9;++i) {
        unsigned j=i%4;
        x[i]=j==3?0:&a[j]; y[i]=j==3?0:&b[j];
    }
    // Modes: separate, self, forward overlap, backward overlap.
    RetainedObject* dx[10]; RetainedObject* dy[10];
    for(unsigned i=0;i<10;++i) { dx[i]=&a[2]; dy[i]=&b[2]; }
    unsigned start= mode==3 ? 1:0;
    RetainedObject** px=mode==0?dx+1:x+(mode==2?1:0);
    RetainedObject** py=mode==0?dy+1:y+(mode==2?1:0);
    riff::pointer_slot_range_copy_retain(x+start,x+start+length,px);
    oracle(y+start,y+start+length,py);
    for(unsigned i=0;i<3;++i)
        if(a[i].opaque!=b[i].opaque || a[i].references!=b[i].references) return 1;
    for(unsigned i=0;i<9;++i) {
        int ix=-1, iy=-1;
        for(int j=0;j<3;++j) { if(x[i]==&a[j]) ix=j; if(y[i]==&b[j]) iy=j; }
        if(ix!=iy || (x[i]==0)!=(y[i]==0)) return 2;
    }
    for(unsigned i=0;i<10;++i) {
        int ix=-1,iy=-1;
        for(int j=0;j<3;++j) { if(dx[i]==&a[j]) ix=j; if(dy[i]==&b[j]) iy=j; }
        if(ix!=iy || (dx[i]==0)!=(dy[i]==0)) return 3;
    }
    return 0;
}
extern "C" int test_main() {
    for(unsigned m=0;m<4;++m) for(unsigned n=0;n<=8;++n) {
        if(run(n,m,0)) return 10;
        if(run(n,m,0xffffffffu)) return 11;
    }
    // Empty/null ranges do not dereference anything. A single null output
    // skips its source load even if that source address is unmapped.
    riff::pointer_slot_range_copy_retain(0,0,0); oracle(0,0,0);
    RetainedObject* const* invalid=reinterpret_cast<RetainedObject* const*>(0x1000u);
    RetainedObject* const* next=reinterpret_cast<RetainedObject* const*>(0x1004u);
    riff::pointer_slot_range_copy_retain(invalid,next,0); oracle(invalid,next,0);
    return 0;
}
