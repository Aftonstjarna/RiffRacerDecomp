#include "impl.hpp"
extern "C" Record40* __attribute__((thiscall)) original_record40_copy_assign(Record40*, const Record40*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs_storage[8];
// Only the oracle uses assembly, supplied separately by the trusted harness.
static int run_case(unsigned dst, unsigned src, unsigned pattern) {
    uint32_t actual[64], oracle[64], expected[64];
    const uint32_t special[10] = {0, 0xffffffffu, 0x80000000u, 0x7f800000u,
        0xff800000u, 0x7fc12345u, 0x7f812345u, 1, 0x3f800000u, 0xdeadbeefu};
    for (unsigned i=0;i<64;++i) {
        uint32_t v = pattern == 0 ? special[i%10] :
            pattern == 1 ? 0u : pattern == 2 ? 0xffffffffu :
            (0x9e3779b9u * (i+1)) ^ (pattern*0x1234567u);
        actual[i]=oracle[i]=expected[i]=v;
    }
    // Independent sequential model also checks untouched source/guard words.
    for (unsigned i=0;i<10;++i) expected[dst+i]=expected[src+i];
    Record40* d = reinterpret_cast<Record40*>(actual+dst);
    const Record40* s = reinterpret_cast<const Record40*>(actual+src);
    Record40* od = reinterpret_cast<Record40*>(oracle+dst);
    const Record40* os = reinterpret_cast<const Record40*>(oracle+src);
    if (&d->operator=(*s) != d) return 1;
    if (original_record40_copy_assign(od,os) != od) return 2;
    if (test_get_fs_head() != 0x13579bdfu) return 4;
    for (unsigned i=0;i<64;++i)
        if (actual[i]!=oracle[i] || actual[i]!=expected[i]) return 3;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0] = 0x13579bdfu;
    if (test_install_fs(fs_storage) != 0) return 5;
    if (test_get_fs_head() != fs_storage[0]) return 6;
    for (unsigned p=0;p<20;++p) {
        // All word-aligned overlap distances, self-copy, adjacent and disjoint.
        for (unsigned d=1;d<=40;++d) {
            int result=run_case(d,16,p);
            if (result) return result;
        }
    }
    return 0;
}
