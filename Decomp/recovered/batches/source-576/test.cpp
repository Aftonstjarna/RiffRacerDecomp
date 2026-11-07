#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_matrix64_initialize_basis(riff::Matrix64*);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static unsigned fs_storage[8];
static unsigned char byte_at(unsigned word, unsigned byte) {
    return static_cast<unsigned char>(word >> (byte * 8));
}
template<unsigned N> static int check(unsigned pattern, unsigned mode) {
    struct Fixture { uint32_t before[N]; riff::Matrix64 matrix; uint32_t after[5]; };
    Fixture recovered, oracle;
    unsigned char* a = reinterpret_cast<unsigned char*>(&recovered);
    unsigned char* b = reinterpret_cast<unsigned char*>(&oracle);
    for (unsigned i=0; i<sizeof(Fixture); ++i) {
        // Includes all-zero, all-ones (NaNs), negative zero, infinities,
        // signaling NaNs, subnormals and varying non-floating sentinel bytes.
        unsigned char value = pattern == 6 ? static_cast<unsigned char>(i*73+19) : byte_at(pattern == 0 ? 0 : pattern == 1 ? 0xffffffffu : pattern == 2 ? 0x80000000u : pattern == 3 ? 0x7f800000u : pattern == 4 ? 0x7f800001u : 1u, i%4);
        a[i]=value; b[i]=value;
    }
    test_set_mxcsr(mode);
    original_matrix64_initialize_basis(&oracle.matrix);
    if (test_get_fs_head()!=fs_storage[0] || test_get_mxcsr()!=mode) return 1;
    recovered.matrix.initialize_basis();
    if (test_get_mxcsr()!=mode) return 2;
    const unsigned begin = N*4;
    for (unsigned i=0; i<sizeof(Fixture); ++i) {
        if (a[i]!=b[i]) return 3;
        if (i>=begin && i<begin+64) {
            unsigned field=(i-begin)/4;
            unsigned expected=(field==0 || field==5 || field==10) ? 0x3f800000u : 0;
            if (a[i]!=byte_at(expected,(i-begin)%4)) return 4;
        } else {
            unsigned char expected = pattern == 6 ? static_cast<unsigned char>(i*73+19) : byte_at(pattern == 0 ? 0 : pattern == 1 ? 0xffffffffu : pattern == 2 ? 0x80000000u : pattern == 3 ? 0x7f800000u : pattern == 4 ? 0x7f800001u : 1u, i%4);
            if (a[i]!=expected) return 5;
        }
    }
    // Repeated initialization must have identical effects.
    original_matrix64_initialize_basis(&oracle.matrix);
    if (test_get_fs_head()!=fs_storage[0]) return 6;
    recovered.matrix.initialize_basis();
    for (unsigned i=0; i<sizeof(Fixture); ++i) if(a[i]!=b[i]) return 7;
    if (test_get_mxcsr()!=mode) return 8;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0x13579bdfu;
    if(test_install_fs(fs_storage)!=0) return 10;
    unsigned saved=test_get_mxcsr();
    int result=0;
    for(unsigned rounding=0; rounding<4; ++rounding)
        for(unsigned denorm=0; denorm<4; ++denorm)
            for(unsigned pattern=0; pattern<7; ++pattern) {
                unsigned mode=0x1f80u | (rounding<<13) | ((denorm&1)<<6) | ((denorm&2)<<14) | 0x25u;
                result=check<1>(pattern,mode); if(result) goto done;
                result=check<2>(pattern,mode); if(result) goto done;
                result=check<3>(pattern,mode); if(result) goto done;
                result=check<4>(pattern,mode); if(result) goto done;
            }
done:
    test_set_mxcsr(saved);
    if(!result) test_write("matrix64 basis: passed\n",23);
    return result;
}
