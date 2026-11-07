#include "impl.hpp"
#include <stdint.h>
extern "C" __m128 __attribute__((thiscall)) original_vector3_dot_sse(const riff::Vector3*, const riff::Vector3*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*, unsigned);
struct Guarded { uint32_t before; riff::Vector3 v; uint32_t after; };
static float from_bits(uint32_t u) { float f; __builtin_memcpy(&f,&u,4); return f; }
static bool same(const void* a,const void* b,unsigned n) {
    const unsigned char* x=(const unsigned char*)a;
    const unsigned char* y=(const unsigned char*)b;
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static int check(Guarded& a,Guarded& b,unsigned mode,bool alias) {
    const Guarded saved_a=a,saved_b=b;
    const riff::Vector3* rhs=alias?&a.v:&b.v;
    test_set_mxcsr(mode);
    __m128 expected=original_vector3_dot_sse(&a.v,rhs);
    unsigned expected_flags=test_get_mxcsr();
    if(!same(&a,&saved_a,sizeof(a)) || !same(&b,&saved_b,sizeof(b))) return 1;
    test_set_mxcsr(mode);
    __m128 actual=a.v.dot_sse(rhs);
    unsigned actual_flags=test_get_mxcsr();
    if(!same(&expected,&actual,16) || expected_flags!=actual_flags) return 2;
    if(!same(&a,&saved_a,sizeof(a)) || !same(&b,&saved_b,sizeof(b))) return 3;
    return 0;
}
extern "C" int test_main() {
    const unsigned saved=test_get_mxcsr();
    const uint32_t values[]={0,0x80000000,0x3f800000,0xbf800000,0x40000000,
        0x4b800000,0xcb800000,0x00800000,1,0x80000001,0x007fffff,
        0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,0x7fc12345,
        0xffc54321,0x7f812345,0xff812346};
    uint32_t state=0x28ad9137;
    for(unsigned mode=0;mode<16;++mode) {
        const unsigned csr=0x1f80 | ((mode&3)<<13) | ((mode&4)?0x8000:0) | ((mode&8)?0x40:0);
        for(unsigned i=0;i<1200;++i) {
            Guarded a={0x13572468,{},0xabcdef01},b={0x87654321,{},0x10fedcba};
            float av[3],bv[3];
            for(unsigned j=0;j<3;++j) {
                state=state*1664525u+1013904223u;
                av[j]=from_bits(i<361?values[(i+j*7)%19]:state);
                state=state*1664525u+1013904223u;
                bv[j]=from_bits(i<361?values[(i/19+j*11)%19]:state);
            }
            a.v.x=av[0]; a.v.y=av[1]; a.v.z=av[2];
            b.v.x=bv[0]; b.v.y=bv[1]; b.v.z=bv[2];
            int result=check(a,b,csr | ((i&1)?0x25:0),false);
            if(!result) result=check(a,b,csr | ((i&1)?0x25:0),true);
            if(result) { test_set_mxcsr(saved); return result; }
        }
    }
    test_set_mxcsr(saved);
    test_write("vector3-dot-sse passed\n",23);
    return 0;
}
