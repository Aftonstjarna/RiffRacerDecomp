#include "impl.hpp"
extern "C" riff::ConvexAabbCachingShape* __attribute__((thiscall))
original_convex_aabb_caching_shape_construct(riff::ConvexAabbCachingShape*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
struct Frame {
    uint32_t before[4];
    riff::ConvexAabbCachingShape object;
    uint32_t after[4];
};
static bool written(unsigned n) {
    return n < 0x1c || (n >= 0x2c && n < 0x30) ||
           (n >= 0x34 && n <= 0x54);
}
static unsigned char seed(unsigned i, unsigned pattern) {
    if (pattern==0) return 0;
    if (pattern==1) return 255;
    if (pattern==2) return 0xa5;
    return static_cast<unsigned char>((i*73u+pattern*29u) ^ (i>>1));
}
extern "C" int test_main() {
    unsigned saved = test_get_mxcsr();
    // All rounding modes, FTZ/DAZ combinations: constructor stores constants
    // without floating arithmetic and must leave the control/status word alone.
    for (unsigned mode=0; mode<16; ++mode) {
        unsigned csr = 0x1f80u | ((mode&3)<<13) |
                       ((mode&4) ? 0x8000u:0) | ((mode&8) ? 0x40u:0);
        test_set_mxcsr(csr);
        for (unsigned pattern=0; pattern<32; ++pattern) {
            Frame a,b;
            unsigned char* x=reinterpret_cast<unsigned char*>(&a);
            unsigned char* y=reinterpret_cast<unsigned char*>(&b);
            for (unsigned i=0;i<sizeof(Frame);++i) x[i]=y[i]=seed(i,pattern);
            if (original_convex_aabb_caching_shape_construct(&a.object)!=&a.object) return 1;
            if (test_get_mxcsr()!=csr) return 2;
            if (b.object.construct()!=&b.object) return 3;
            if (test_get_mxcsr()!=csr) return 4;
            for (unsigned i=0;i<sizeof(Frame);++i) {
                if (x[i]!=y[i]) return 5;
                bool changed = i>=16 && i<16+0x58 && written(i-16);
                if (!changed && x[i]!=seed(i,pattern)) return 6;
            }
            // A repeated construction must preserve all untouched storage.
            if (original_convex_aabb_caching_shape_construct(&a.object)!=&a.object) return 7;
            b.object.construct();
            for (unsigned i=0;i<sizeof(Frame);++i) if(x[i]!=y[i]) return 8;
        }
    }
    test_set_mxcsr(saved);
    return 0;
}
