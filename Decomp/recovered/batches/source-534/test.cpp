#include "impl.hpp"
extern "C" void __attribute__((fastcall)) original_record12_default_initialize(Record12*, uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs_storage[4];
extern "C" void test_write(const char*, unsigned);

struct GuardedRecords {
    uint32_t before[4];
    Record12 records[67];
    uint32_t after[4];
};
static GuardedRecords recovered;
static GuardedRecords oracle;

static void seed(GuardedRecords& buffer, uint32_t salt)
{
    for (unsigned i = 0; i != 4; ++i) {
        buffer.before[i] = salt ^ (0x12345678u + i);
        buffer.after[i] = salt ^ (0x87654321u + i);
    }
    for (unsigned i = 0; i != 67; ++i) {
        buffer.records[i].field0 = salt ^ (0x81828384u + i);
        buffer.records[i].field4 = salt ^ (0x42434445u + i);
        buffer.records[i].field8 = salt ^ (0xf1f2f3f4u + i);
    }
}
static bool equal(const GuardedRecords& a, const GuardedRecords& b)
{
    const unsigned char* x = reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* y = reinterpret_cast<const unsigned char*>(&b);
    for (unsigned i = 0; i != sizeof(a); ++i)
        if (x[i] != y[i]) return false;
    return true;
}
extern "C" int test_main()
{
    fs_storage[0] = 0x13579bdfu;
    if (test_install_fs(fs_storage) != 0) return 7;
    // Null is a no-op only for count 0 or 1: count 2 would write address 12.
    original_record12_default_initialize(0, 0);
    if (test_get_fs_head() != fs_storage[0]) return 8;
    record12_default_initialize(0, 0);
    original_record12_default_initialize(0, 1);
    if (test_get_fs_head() != fs_storage[0]) return 8;
    record12_default_initialize(0, 1);
    // Invalid non-null addresses are also untouched with count zero.
    original_record12_default_initialize(reinterpret_cast<Record12*>(1), 0);
    if (test_get_fs_head() != fs_storage[0]) return 8;
    record12_default_initialize(reinterpret_cast<Record12*>(1), 0);
    const unsigned counts[] = {0, 1, 2, 3, 16, 64};
    const uint32_t salts[] = {0, 0xffffffffu, 0x5577aaccu};
    for (unsigned s = 0; s != 3; ++s) {
        for (unsigned c = 0; c != 6; ++c) {
            seed(recovered, salts[s]);
            seed(oracle, salts[s]);
            unsigned n = counts[c];
            original_record12_default_initialize(oracle.records + 2, n);
            if (test_get_fs_head() != fs_storage[0]) return 8;
            record12_default_initialize(recovered.records + 2, n);
            if (!equal(recovered, oracle)) return 1;
            // Independent expectation for all records, including untouched prefix/suffix.
            for (unsigned i = 0; i != 67; ++i) {
                bool written = i >= 2 && i < 2 + n;
                if (recovered.records[i].field0 != (written ? 0 : (salts[s] ^ (0x81828384u+i)))) return 2;
                if (recovered.records[i].field4 != (written ? 0xffffffffu : (salts[s] ^ (0x42434445u+i)))) return 3;
                if (recovered.records[i].field8 != (written ? 0 : (salts[s] ^ (0xf1f2f3f4u+i)))) return 4;
            }
            for (unsigned i = 0; i != 4; ++i) {
                if (recovered.before[i] != (salts[s] ^ (0x12345678u+i))) return 5;
                if (recovered.after[i] != (salts[s] ^ (0x87654321u+i))) return 6;
            }
        }
    }
    test_write("record12 tests passed\n", 22);
    return 0;
}
