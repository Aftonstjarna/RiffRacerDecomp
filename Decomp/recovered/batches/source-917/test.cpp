#include "impl.hpp"
extern "C" void __attribute__((fastcall)) original_record48_default_construct_range(Record48*, uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static Record48 recovered[68], oracle[68];
static unsigned fsStorage[16];
static unsigned char pattern(unsigned i, unsigned seed) {
    return static_cast<unsigned char>((i * 73u + seed * 29u) ^ (i >> 3));
}
extern "C" int test_main() {
    fsStorage[0] = 0x13579bdfu;
    if (test_install_fs(fsStorage) != 0) return 1;
    for (unsigned seed = 0; seed != 8; ++seed) {
        for (unsigned start = 0; start != 4; ++start) {
            for (unsigned count = 0; count <= 64; ++count) {
                unsigned char* a = reinterpret_cast<unsigned char*>(recovered);
                unsigned char* b = reinterpret_cast<unsigned char*>(oracle);
                for (unsigned i = 0; i != sizeof(recovered); ++i) a[i] = b[i] = pattern(i, seed);
                record48_default_construct_range(recovered + start, count);
                original_record48_default_construct_range(oracle + start, count);
                if (test_get_fs_head() != fsStorage[0]) return 2;
                for (unsigned i = 0; i != sizeof(recovered); ++i) {
                    bool inside = i >= start * 48 && i < (start + count) * 48;
                    unsigned offset = i % 48;
                    bool cleared = inside && (offset < 36 || (offset >= 40 && offset <= 44));
                    unsigned char expected = cleared ? 0 : pattern(i, seed);
                    if (a[i] != b[i] || a[i] != expected) return 3;
                }
            }
        }
    }
    // No memory access for zero count, even with an invalid address.
    Record48* invalid = reinterpret_cast<Record48*>(static_cast<uintptr_t>(1));
    record48_default_construct_range(invalid, 0);
    original_record48_default_construct_range(invalid, 0);
    if (test_get_fs_head() != fsStorage[0]) return 4;
    record48_default_construct_range(0, 0);
    original_record48_default_construct_range(0, 0);
    if (test_get_fs_head() != fsStorage[0]) return 5;
    // Null is skipped once; null with count > 1 would next write at address 48.
    record48_default_construct_range(0, 1);
    original_record48_default_construct_range(0, 1);
    if (test_get_fs_head() != fsStorage[0]) return 6;
    test_write("record48 differential tests passed\n", 35);
    return 0;
}
