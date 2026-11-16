#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_simplex_result_reset(SimplexResult*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);

struct Guarded { uint32_t before[4]; SimplexResult value; uint32_t after[4]; };
static void fill(Guarded& v, unsigned seed) {
    unsigned char* p = reinterpret_cast<unsigned char*>(&v);
    for (unsigned i=0; i<sizeof(v); ++i) p[i]=static_cast<unsigned char>(seed+i*73u);
}
static bool same(const Guarded& a, const Guarded& b) {
    const unsigned char* x=reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* y=reinterpret_cast<const unsigned char*>(&b);
    for (unsigned i=0; i<sizeof(a); ++i) if(x[i]!=y[i]) return false;
    return true;
}
extern "C" int test_main() {
    uint32_t fsStorage[8] = {0xabcdef01u};
    if(test_install_fs(fsStorage)!=0) return 1;
    // Exhaust every flags value, including all preserved high bits. Varied
    // byte patterns exercise every possible old status/weight/padding byte.
    for(unsigned f=0; f<65536u; ++f) {
        Guarded recovered, oracle, expected;
        fill(recovered, f); fill(oracle, f); fill(expected, f);
        recovered.value.flags=oracle.value.flags=expected.value.flags=static_cast<uint16_t>(f);
        unsigned char* e=reinterpret_cast<unsigned char*>(&expected.value);
        e[0x10]&=0xf0u;
        for(unsigned i=0x14; i<=0x24; ++i) e[i]=0;
        recovered.value.reset();
        original_simplex_result_reset(&oracle.value);
        if(test_get_fs_head()!=fsStorage[0]) return 2;
        if(!same(recovered,oracle) || !same(recovered,expected)) return 3;
        recovered.value.reset();
        original_simplex_result_reset(&oracle.value);
        if(test_get_fs_head()!=fsStorage[0]) return 4;
        if(!same(recovered,oracle) || !same(recovered,expected)) return 5;
    }
    test_write("simplex-result-reset passed\n",28);
    return 0;
}
