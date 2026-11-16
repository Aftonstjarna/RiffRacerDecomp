#include "impl.hpp"
extern "C" riff::Block64* __attribute__((thiscall)) original_block64_zero_initialize(riff::Block64*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" unsigned test_get_mxcsr();
struct Envelope {
    uint32_t before[10]; // same subobject offset as the observed callers
    riff::Block64 block;
    uint32_t after[16];
};
static void fill(Envelope& e, unsigned pattern) {
    for (unsigned i = 0; i != 10; ++i) e.before[i] = 0xa5190000u + i;
    for (unsigned i = 0; i != 16; ++i) {
        e.block.words[i] = pattern == 0 ? 0 : pattern == 1 ? 0xffffffffu :
            pattern == 2 ? (1u << (i * 2)) : (0x9e3779b9u * (i + pattern));
        e.after[i] = 0x5ae10000u + i;
    }
}
extern "C" int test_main() {
    uint32_t fs_storage[8] = {0x13579bdfu};
    if (test_install_fs(fs_storage) != 0) return 1;
    for (unsigned pattern = 0; pattern != 67; ++pattern) {
        Envelope a, b;
        fill(a, pattern); fill(b, pattern);
        for (unsigned repeat = 0; repeat != 2; ++repeat) {
            unsigned mxcsr = test_get_mxcsr();
            if (original_block64_zero_initialize(&a.block) != &a.block) return 2;
            if (test_get_fs_head() != fs_storage[0]) return 3;
            if (test_get_mxcsr() != mxcsr) return 4;
            if (b.block.zero_initialize() != &b.block) return 5;
            for (unsigned i = 0; i != 16; ++i) {
                if (a.block.words[i] != 0 || b.block.words[i] != 0) return 6;
                if (a.after[i] != 0x5ae10000u + i || b.after[i] != a.after[i]) return 7;
            }
            for (unsigned i = 0; i != 10; ++i)
                if (a.before[i] != 0xa5190000u + i || b.before[i] != a.before[i]) return 8;
        }
    }
    return 0;
}
