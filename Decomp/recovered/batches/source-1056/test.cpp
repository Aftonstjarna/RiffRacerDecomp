#include "impl.hpp"
extern "C" uint32_t __attribute__((thiscall)) original_record6_capacity_growth(const Record6Storage *, uint32_t);
extern "C" int test_install_fs(void *);
extern "C" unsigned test_get_fs_head();

static uint32_t fs_storage[16];
static int check(uint32_t begin, uint32_t end, uint32_t request, uint32_t middle) {
    Record6Storage a = {begin, middle, end};
    Record6Storage b = a;
    const uint32_t actual = a.capacity_growth(request);
    const uint32_t expected = original_record6_capacity_growth(&b, request);
    return actual == expected && a.begin_address == begin && b.begin_address == begin
        && a.current_end_address == middle && b.current_end_address == middle
        && a.allocation_end_address == end && b.allocation_end_address == end
        && test_get_fs_head() == 0x13579bdfu;
}
extern "C" int test_main() {
    fs_storage[0] = 0x13579bdfu;
    if (test_install_fs(fs_storage) != 0 || test_get_fs_head() != fs_storage[0]) return 1;
    const uint32_t differences[] = {0,1,5,6,7,11,12,13, 0x3fffffffu, 0x40000000u,
        0x55555550u,0x55555554u,0x55555555u,0x55555556u,0x7fffffffu,
        0x80000000u,0x80000001u,0xfffffff4u,0xfffffffau,0xffffffffu};
    const uint32_t requests[] = {0,1,2,3,10,0x1fffffffu,0x2aaaaaaau,0x2aaaaaabu,0x7fffffffu,0xffffffffu};
    for (unsigned i=0; i<sizeof(differences)/sizeof(differences[0]); ++i)
        for (unsigned j=0; j<sizeof(requests)/sizeof(requests[0]); ++j) {
            if (!check(0x12345678u, 0x12345678u+differences[i], requests[j], 0xdeadbeefu)) return 2;
        }
    uint32_t state = 0x12345678u;
    for (unsigned i=0; i<10000; ++i) {
        state = state * 1664525u + 1013904223u; uint32_t begin = state;
        state = state * 1664525u + 1013904223u; uint32_t end = state;
        state = state * 1664525u + 1013904223u; uint32_t request = state;
        if (!check(begin, end, request, state ^ 0xa5a5a5a5u)) return 3;
    }
    return 0;
}
