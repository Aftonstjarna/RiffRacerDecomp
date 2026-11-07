#include "impl.hpp"
extern "C" void original_narrow_record24_default_initialize(
    riff::NarrowRecord24*, uint32_t, ...); // GCC i386 cdecl; caller cleans stack
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static uint32_t fs_storage[8];
static riff::NarrowRecord24 recovered[19], oracle[19];
static unsigned char before[sizeof(recovered)];
static int run(unsigned start, unsigned count, unsigned seed) {
    unsigned char* a = reinterpret_cast<unsigned char*>(recovered);
    unsigned char* b = reinterpret_cast<unsigned char*>(oracle);
    for (unsigned i=0; i<sizeof(recovered); ++i)
        before[i] = a[i] = b[i] = static_cast<unsigned char>(i * 37u + seed);
    riff::narrow_record24_default_initialize(recovered + start, count);
    original_narrow_record24_default_initialize(oracle + start, count,
                                                0x12345678u, 0u, 0xabcdef01u);
    if (test_get_fs_head() != fs_storage[0]) return 1;
    for (unsigned i=0; i<sizeof(recovered); ++i) {
        unsigned char expected = before[i];
        if (i >= start*24 && i < (start+count)*24) {
            unsigned offset = (i-start*24)%24;
            if (offset == 0 || (offset >=16 && offset <20) || offset>=21)
                expected=0;
            if (offset==20) expected=15;
        }
        if (a[i]!=b[i] || a[i]!=expected) return 2;
    }
    return 0;
}
extern "C" int test_main() {
    fs_storage[0] = 0x13579bdfu;
    if (test_install_fs(fs_storage) != 0) return 10;
    // Empty ranges never dereference the supplied address; null/count=1
    // skips the only iteration. Null/count>1 would write at address 24.
    riff::NarrowRecord24* cases[3] = {0, reinterpret_cast<riff::NarrowRecord24*>(1), recovered};
    for (unsigned i=0;i<3;++i) {
        riff::narrow_record24_default_initialize(cases[i],0);
        original_narrow_record24_default_initialize(cases[i],0);
        if(test_get_fs_head()!=fs_storage[0]) return 11;
    }
    riff::narrow_record24_default_initialize(0,1);
    original_narrow_record24_default_initialize(0,1);
    if(test_get_fs_head()!=fs_storage[0]) return 12;
    for(unsigned seed=0;seed<256;seed+=17)
        for(unsigned count=0;count<=17;++count)
            if(run(1,count,seed)) return 20;
    test_write("record24 checks passed\n",23);
    return 0;
}
