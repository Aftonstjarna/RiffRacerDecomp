#include "impl.hpp"
// GCC regparm(3) supplies EAX(unused), EDX(end), ECX(begin), with destination
// on the caller-cleaned stack. fastcall would incorrectly assume callee cleanup.
extern "C" void* original_record20_range_copy(uintptr_t unused, const void* end,
    const void* begin, void* destination) __attribute__((regparm(3)));
static unsigned char a[512], b[512];
static void init() {
    for (unsigned i=0;i<512;++i) a[i]=b[i]=static_cast<unsigned char>((i*73u)^(i>>2)^0xa5u);
}
static bool same() {
    for (unsigned i=0;i<512;++i) if (a[i]!=b[i]) return false;
    return true;
}
extern "C" int test_main() {
    // Every alignment, forward/backward overlap (including partial record),
    // exact alias, empty, single and multi-record ranges. Compare all guard bytes.
    for (unsigned n=0;n<=8;++n) {
        for (unsigned alignment=0;alignment<16;++alignment) {
            for (int delta=-45;delta<=45;++delta) {
                init();
                unsigned s=128+alignment;
                unsigned d=static_cast<unsigned>(static_cast<int>(s)+delta);
                void* expected=original_record20_range_copy(0,b+s+n*20,b+s,b+d);
                void* actual=record20_range_copy(a+s,a+s+n*20,a+d);
                if (reinterpret_cast<uintptr_t>(expected)-reinterpret_cast<uintptr_t>(b)
                    != reinterpret_cast<uintptr_t>(actual)-reinterpret_cast<uintptr_t>(a)) return 1;
                if (!same()) return 2;
            }
        }
    }
    init();
    // Empty ranges never dereference either pointer, even null/synthetic ones.
    const uintptr_t starts[]={0,1,0xfffffff0u};
    const uintptr_t destinations[]={0,7,0xfffffffcu};
    for(unsigned i=0;i<3;++i) for(unsigned j=0;j<3;++j) {
        const void* s=reinterpret_cast<const void*>(starts[i]);
        void* d=reinterpret_cast<void*>(destinations[j]);
        if(original_record20_range_copy(0,s,s,d)!=record20_range_copy(s,s,d)) return 3;
    }
    // A single null destination suppresses even an invalid source read.
    const void* s=reinterpret_cast<const void*>(1);
    const void* e=reinterpret_cast<const void*>(21);
    if(original_record20_range_copy(0,e,s,0)!=reinterpret_cast<void*>(20)) return 4;
    if(record20_range_copy(s,e,0)!=reinterpret_cast<void*>(20)) return 5;
    if(!same()) return 6;
    return 0;
}
