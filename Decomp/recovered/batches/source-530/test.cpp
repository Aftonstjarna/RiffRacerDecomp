#include "impl.hpp"
extern "C" uint32_t* __attribute__((thiscall)) original_matrix_column3_extract(const riff::Matrix*, uint32_t*, uint32_t);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" void test_write(const char*, unsigned);
static const uint32_t patterns[] = {
    0,0x80000000u,0x3f800000u,0xbf800000u,
    0x7f800000u,0xff800000u,0x7fc12345u,0x7f812345u,
    1,0x80000001u,0x007fffffu,0x00800000u,
    0xffffffffu,0x12345678u,0xdeadbeefu,0x40490fdbu
};
struct Fixture { uint32_t before[4]; riff::Matrix matrix; uint32_t after[4]; uint32_t out[8]; };
static void initialize(Fixture& f, unsigned seed) {
    for(unsigned i=0;i<4;++i) { f.before[i]=0xabc00000u+i; f.after[i]=0xdef00000u+i; }
    for(unsigned i=0;i<16;++i) f.matrix.words[i]=patterns[(i+seed)%16];
    for(unsigned i=0;i<8;++i) f.out[i]=0x55550000u+i;
}
static bool equal(const Fixture& a, const Fixture& b) {
    for(unsigned i=0;i<4;++i) if(a.before[i]!=b.before[i] || a.after[i]!=b.after[i]) return false;
    for(unsigned i=0;i<16;++i) if(a.matrix.words[i]!=b.matrix.words[i]) return false;
    for(unsigned i=0;i<8;++i) if(a.out[i]!=b.out[i]) return false;
    return true;
}
extern "C" int test_main() {
    const unsigned saved=test_get_mxcsr();
    for(unsigned mode=0;mode<2;++mode) {
        // Mask exceptions; exercise both gradual underflow and FTZ/DAZ.
        const unsigned control=mode ? 0x9fc0u : 0x1f80u;
        test_set_mxcsr(control);
        for(unsigned seed=0;seed<16;++seed) for(unsigned column=0;column<8;++column) {
            // 0..3 are matrix columns. 4..7 check unchecked in-object access.
            // -1 selects a separate output, others overlap every legal span.
            for(int offset=-1;offset<=12;++offset) {
                Fixture a,b; initialize(a,seed); initialize(b,seed);
                uint32_t* pa=offset<0 ? a.out+2 : a.matrix.words+offset;
                uint32_t* pb=offset<0 ? b.out+2 : b.matrix.words+offset;
                uint32_t* ra=a.matrix.column3(pa,column);
                uint32_t* rb=original_matrix_column3_extract(&b.matrix,pb,column);
                if(ra!=pa || rb!=pb || !equal(a,b) || test_get_mxcsr()!=control) {
                    test_set_mxcsr(saved); return 1;
                }
                if(offset<0) {
                    if(pa[0]!=patterns[(column+seed)%16] ||
                       pa[1]!=patterns[(column+4+seed)%16] ||
                       pa[2]!=patterns[(column+8+seed)%16] || pa[3]!=0) {
                        test_set_mxcsr(saved); return 2;
                    }
                }
            }
        }
    }
    test_set_mxcsr(saved);
    test_write("matrix-column3-extract: passed\n",31);
    return 0;
}
