#include "impl.hpp"
extern "C" uint32_t __attribute__((thiscall)) original_wide_entry_growth_policy(const WideEntryVector*, uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();

extern "C" int test_main() {
    uint32_t fs_storage[16] = {};
    fs_storage[0] = 0xffffffffu;
    if (test_install_fs(fs_storage) != 0) return 1;
    const unsigned fs_head = test_get_fs_head();
    const uint32_t differences[] = {0, 1, 27, 28, 29, 56, 84, 280, 0x7fffffffu, 0x80000000u, 0xffffffffu, 0xffffffe4u, 0xffffffc8u, 0xffffffc7u, 0x7fffffe0u, 0x40000000u};
    const uint32_t requests[] = {0, 1, 2, 3, 4, 10, 0x09249248u, 0x09249249u, 0x0924924au, 0x7fffffffu, 0x80000000u, 0xffffffffu};
    for (unsigned i = 0; i < sizeof(differences)/sizeof(differences[0]); ++i) {
        for (unsigned j = 0; j < sizeof(requests)/sizeof(requests[0]); ++j) {
            WideEntryVector v = {0xabcdeff0u, 0x12345678u, 0xabcdeff0u + differences[i]};
            const WideEntryVector before = v;
            uint32_t expected = original_wide_entry_growth_policy(&v, requests[j]);
            if (test_get_fs_head() != fs_head) return 2;
            if (v.begin != before.begin || v.end != before.end || v.capacity_end != before.capacity_end) return 3;
            if (v.growth_policy(requests[j]) != expected) return 4;
            if (v.begin != before.begin || v.end != before.end || v.capacity_end != before.capacity_end) return 5;
        }
    }
    // Probe large wrapped address differences around a 32-bit boundary.
    for (uint32_t n = 102261120u; n < 102261135u; ++n) {
        WideEntryVector v = {0u, 0xdeadbeefu, n * 28u};
        const WideEntryVector before = v;
        uint32_t expected = original_wide_entry_growth_policy(&v, 7);
        if (test_get_fs_head() != fs_head) return 6;
        if (v.begin != before.begin || v.end != before.end || v.capacity_end != before.capacity_end) return 7;
        if (v.growth_policy(7) != expected) return 8;
    }
    return 0;
}
