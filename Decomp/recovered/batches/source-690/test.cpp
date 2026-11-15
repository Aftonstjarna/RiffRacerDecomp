#include "impl.hpp"
#include <stddef.h>
extern "C" void __attribute__((thiscall)) original_matrix3_copy_storage(void*, const void*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*, unsigned);
// Freestanding support, deliberately bytewise. No runtime libraries are linked.
extern "C" void* memcpy(void* d, const void* s, size_t n) {
    unsigned char* out = static_cast<unsigned char*>(d);
    const unsigned char* in = static_cast<const unsigned char*>(s);
    for (size_t i=0; i<n; ++i) out[i]=in[i];
    return d;
}
extern "C" void* memset(void* d, int c, size_t n) {
    unsigned char* out=static_cast<unsigned char*>(d);
    for(size_t i=0;i<n;++i) out[i]=static_cast<unsigned char>(c);
    return d;
}
struct Envelope {
    unsigned char before[32];
    Matrix3Storage matrix;
    unsigned char after[80];
};
static_assert(sizeof(Envelope)==160, "test byte layout");
extern "C" int test_main() {
    const unsigned saved = test_get_mxcsr();
    const unsigned patterns[] = {0, 0xffffffffu, 0x80000000u, 0x7f800000u,
        0xff800000u, 0x7fc12345u, 0x7f800001u, 1u, 0x007fffffu,
        0x3f800000u, 0xdeadbeefu};
    for(unsigned mode=0;mode<4;++mode) {
        const unsigned control=(saved & ~0xe07fu) | 0x1f80u |
            ((mode&1)?0x8040u:0u) | ((mode&2)?0x6000u:0u);
        test_set_mxcsr(control);
        for(unsigned seed=0;seed<32;++seed) {
            // Includes all forward/backward partial overlaps, self-copy,
            // adjacent/disjoint buffers, and byte-unaligned source addresses.
            for(unsigned src=0;src<=112;++src) {
                Envelope recovered, oracle;
                unsigned char* a=reinterpret_cast<unsigned char*>(&recovered);
                unsigned char* b=reinterpret_cast<unsigned char*>(&oracle);
                for(unsigned i=0;i<160;++i) {
                    unsigned v=patterns[(i/4+seed)%11];
                    a[i]=b[i]=static_cast<unsigned char>((v >> ((i%4)*8)) ^ (seed*13));
                }
                recovered.matrix.copy_storage(a+src);
                original_matrix3_copy_storage(&oracle.matrix,b+src);
                if(test_get_mxcsr()!=control) { test_set_mxcsr(saved); return 1; }
                for(unsigned i=0;i<160;++i) {
                    if(a[i]!=b[i]) { test_set_mxcsr(saved); return 2; }
                    if((i<32 || i>=80)) {
                        unsigned v=patterns[(i/4+seed)%11];
                        unsigned char initial=static_cast<unsigned char>((v >> ((i%4)*8)) ^ (seed*13));
                        if(a[i]!=initial) { test_set_mxcsr(saved); return 3; }
                    }
                }
            }
        }
    }
    test_set_mxcsr(saved);
    test_write("PASS matrix3-copy-storage\n",26);
    return 0;
}
