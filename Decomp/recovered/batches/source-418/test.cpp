#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_narrow_set_length(NarrowString*, uint32_t);

static void fill(void* p, unsigned n, unsigned char value) {
    unsigned char* b = static_cast<unsigned char*>(p);
    for (unsigned i=0; i<n; ++i) b[i] = value;
}
static bool same(const void* a, const void* b, unsigned n) {
    const unsigned char* x = static_cast<const unsigned char*>(a);
    const unsigned char* y = static_cast<const unsigned char*>(b);
    for (unsigned i=0; i<n; ++i) if (x[i] != y[i]) return false;
    return true;
}
struct Guarded { uint32_t before[4]; NarrowString s; uint32_t after[4]; };
static bool run(uint32_t cap, uint32_t len) {
    Guarded recovered, oracle, expected;
    unsigned char recovered_data[96], oracle_data[96], expected_data[96];
    fill(&recovered, sizeof(recovered), 0xa5);
    recovered.s.capacity = cap;
    recovered.s.length = 0xdeadbeef;
    fill(recovered_data, sizeof(recovered_data), 0x6d);
    fill(oracle_data, sizeof(oracle_data), 0x6d);
    fill(expected_data, sizeof(expected_data), 0x6d);
    // Interior pointers leave an explicit leading and trailing buffer guard.
    if (cap >= 16) recovered.s.storage.heap_data = reinterpret_cast<char*>(recovered_data+8);
    oracle = recovered;
    if (cap >= 16) oracle.s.storage.heap_data = reinterpret_cast<char*>(oracle_data+8);
    expected = recovered;
    expected.s.length = len;
    if (cap >= 16) expected_data[8+len] = 0;
    else expected.s.storage.inline_data[len] = 0;
    recovered.s.set_length(len);
    original_narrow_set_length(&oracle.s, len);
    if (!same(&recovered, &expected, sizeof(expected))) return false;
    if (!same(recovered_data, expected_data, sizeof(expected_data))) return false;
    if (!same(oracle_data, expected_data, sizeof(expected_data))) return false;
    // Different heap backing addresses are the sole expected object difference.
    if (cap >= 16) {
        if (oracle.s.storage.heap_data != reinterpret_cast<char*>(oracle_data+8)) return false;
        oracle.s.storage.heap_data = recovered.s.storage.heap_data;
    }
    return same(&oracle, &expected, sizeof(expected));
}
extern "C" int test_main() {
    const uint32_t inline_caps[] = {0, 1, 14, 15};
    for (unsigned c=0; c<4; ++c)
        for (uint32_t n=0; n<16; ++n)
            if (!run(inline_caps[c], n)) return 1;
    const uint32_t heap_caps[] = {16, 17, 31, 0x7fffffffu, 0x80000000u, 0xffffffffu};
    const uint32_t lengths[] = {0, 1, 15, 16, 17, 31, 63, 79};
    for (unsigned c=0; c<6; ++c)
        for (unsigned n=0; n<8; ++n)
            if (!run(heap_caps[c], lengths[n])) return 2;
    return 0;
}
