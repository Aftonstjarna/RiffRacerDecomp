#include "impl.hpp"
extern "C" ResourceRecord24* __attribute__((thiscall))
original_resource_record24_construct(ResourceRecord24*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
struct Guarded {
    uint32_t before[4];
    ResourceRecord24 record;
    uint32_t after[4];
};
static void fill(Guarded& g, unsigned seed) {
    for (unsigned i=0; i<4; ++i) {
        g.before[i] = seed ^ (0x12345678u+i);
        g.after[i] = seed ^ (0xabcdef01u+i);
    }
    for (unsigned i=0; i<6; ++i) g.record.fields[i]=seed;
}
extern "C" int test_main() {
    unsigned fs[4] = {0x13579bdfu,0,0,0};
    if (test_install_fs(fs)!=0) return 1;
    const unsigned seeds[] = {0,0xffffffffu,0x80000000u,1,0x55555555u,0xaaaaaaaau,0xdeadbeefu};
    for (unsigned s=0; s<sizeof(seeds)/sizeof(seeds[0]); ++s) {
        Guarded actual, expected;
        fill(actual,seeds[s]); fill(expected,seeds[s]);
        for (unsigned repeat=0; repeat<2; ++repeat) {
            if (original_resource_record24_construct(&expected.record)!=&expected.record) return 2;
            if (test_get_fs_head()!=fs[0]) return 3;
            if (actual.record.construct()!=&actual.record) return 4;
            for (unsigned i=0; i<6; ++i) {
                const unsigned value=(i==3)?0xffffffffu:0;
                if (actual.record.fields[i]!=expected.record.fields[i] || actual.record.fields[i]!=value) return 5;
            }
            for (unsigned i=0; i<4; ++i) {
                if (actual.before[i]!=(seeds[s]^(0x12345678u+i)) || expected.before[i]!=actual.before[i]) return 6;
                if (actual.after[i]!=(seeds[s]^(0xabcdef01u+i)) || expected.after[i]!=actual.after[i]) return 7;
            }
        }
    }
    return 0;
}
