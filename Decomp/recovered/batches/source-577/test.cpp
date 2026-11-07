#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_matrix48_initialize_basis(Matrix48*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
struct Guarded {
    uint32_t before[5];
    Matrix48 matrix;
    uint32_t after[7];
};
static void fill(void* p, unsigned n, uint32_t seed) {
    unsigned char* b = static_cast<unsigned char*>(p);
    for (unsigned i=0; i<n; ++i) {
        seed = seed * 1664525u + 1013904223u;
        b[i] = static_cast<unsigned char>(seed >> 24);
    }
}
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for (unsigned i=0; i<n; ++i) if (x[i]!=y[i]) return false;
    return true;
}
static uint32_t bits(const float& f) {
    uint32_t v=0;
    unsigned char* d=reinterpret_cast<unsigned char*>(&v);
    const unsigned char* s=reinterpret_cast<const unsigned char*>(&f);
    for (unsigned i=0; i<4; ++i) d[i]=s[i];
    return v;
}
extern "C" int test_main() {
    const unsigned saved=test_get_mxcsr();
    const unsigned modes[]={0x1f80u,0x3f80u,0x5f80u,0x7f80u,0x9fc0u,0x1fbfu};
    for (unsigned m=0; m<6; ++m) {
        test_set_mxcsr(modes[m]);
        for (unsigned trial=0; trial<128; ++trial) {
            Guarded a,b,initial;
            fill(&a,sizeof(a),trial);
            // Explicit signed zero, infinity, signaling/quiet NaN and subnormal
            // payloads are input bytes only, never evaluated as floats.
            const uint32_t patterns[]={0u,0xffffffffu,0x80000000u,0x7f800000u,
                0xff800000u,0x7f800001u,0x7fc12345u,1u};
            if(trial<8) {
                unsigned char* p=reinterpret_cast<unsigned char*>(&a.matrix);
                const unsigned char* v=reinterpret_cast<const unsigned char*>(&patterns[trial]);
                for(unsigned i=0;i<48;++i) p[i]=v[i%4];
            }
            b=a; initial=a;
            original_matrix48_initialize_basis(&a.matrix);
            if(test_get_mxcsr()!=modes[m]) return 1;
            b.matrix.initialize_basis();
            if(test_get_mxcsr()!=modes[m]) return 2;
            if(!equal(&a,&b,sizeof(a))) return 3;
            if(!equal(a.before,initial.before,sizeof(a.before)) ||
               !equal(a.after,initial.after,sizeof(a.after))) return 4;
            for(unsigned r=0;r<3;++r) for(unsigned c=0;c<4;++c)
                if(bits(a.matrix.basis[r][c]) != (r==c?0x3f800000u:0u)) return 5;
            original_matrix48_initialize_basis(&a.matrix);
            b.matrix.initialize_basis();
            if(!equal(&a,&b,sizeof(a)) || test_get_mxcsr()!=modes[m]) return 6;
        }
    }
    test_set_mxcsr(saved);
    return 0;
}
