#include "impl.hpp"

// ECX holds the value; fastcall supplies ECX for its first integer argument.
extern "C" uint32_t __attribute__((fastcall)) original_script_instruction_open_result(uint32_t);
extern "C" int test_install_fs(void *);
extern "C" unsigned test_get_fs_head();

static uint32_t fs_storage[8];
static int check(uint32_t word) {
    const uint32_t head = 0x13579bdfu;
    fs_storage[0] = head;
    if (test_install_fs(fs_storage) != 0) return 1;
    uint32_t actual = original_script_instruction_open_result(word);
    if (test_get_fs_head() != head || fs_storage[0] != head) return 2;
    if (actual != script_instruction_open_result(word)) return 3;
    return 0;
}
extern "C" int test_main() {
    // Every opcode, each individual bit, and combined field boundary patterns.
    for (uint32_t op = 0; op < 64; ++op) {
        if (check(op) || check(op | 0x007fffc0u) ||
            check(op | 0xff800000u) || check(op | 0xffffffc0u)) return 1;
        for (unsigned bit = 6; bit < 32; ++bit)
            if (check(op | (uint32_t(1) << bit))) return 2;
    }
    uint32_t state = 0x12345678u;
    for (unsigned i = 0; i < 4096; ++i) {
        state = state * 1664525u + 1013904223u;
        if (check(state)) return 3;
    }
    return 0;
}
