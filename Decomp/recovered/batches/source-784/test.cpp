#include "impl.hpp"
extern "C" uint32_t __attribute__((thiscall)) original_script_table_length(const ScriptTable*);
extern "C" uint32_t __attribute__((fastcall)) original_script_table_hash_boundary(const ScriptTable*, uint32_t);
extern "C" uint32_t RIFF_FASTCALL script_table_hash_boundary(const ScriptTable* t, uint32_t n) {
    return original_script_table_hash_boundary(t, n);
}
extern "C" void* memcpy(void* d, const void* s, unsigned n) {
    unsigned char* p = static_cast<unsigned char*>(d);
    const unsigned char* q = static_cast<const unsigned char*>(s);
    for (unsigned i = 0; i < n; ++i) { p[i] = q[i]; }
    return d;
}
static bool same(const void* a, const void* b, unsigned n) {
    const unsigned char* p = static_cast<const unsigned char*>(a);
    const unsigned char* q = static_cast<const unsigned char*>(b);
    for (unsigned i = 0; i < n; ++i) {
        if (p[i] != q[i]) { return false; }
    }
    return true;
}
struct Node { ScriptValue value; float key; uint32_t keyTag; Node* next; };
static ScriptValue values[16];
static Node nodes[2];
static int check(ScriptTable& t, bool known, uint32_t expected) {
    ScriptTable before = t;
    ScriptValue saved[16];
    Node savedNodes[2];
    memcpy(saved, values, sizeof(values));
    memcpy(savedNodes, nodes, sizeof(nodes));
    const uint32_t a = original_script_table_length(&t);
    if (!same(&t, &before, sizeof(t)) || !same(values, saved, sizeof(values)) ||
        !same(nodes, savedNodes, sizeof(nodes))) { return 1; }
    const uint32_t b = t.length();
    if (a != b || (known && b != expected)) { return 2; }
    if (!same(&t, &before, sizeof(t)) || !same(values, saved, sizeof(values)) ||
        !same(nodes, savedNodes, sizeof(nodes))) { return 3; }
    return 0;
}
extern "C" int test_main() {
    ScriptTable t;
    unsigned char* raw = reinterpret_cast<unsigned char*>(&t);
    for (unsigned i = 0; i < sizeof(t); ++i) { raw[i] = static_cast<unsigned char>(0x51 + i); }
    t.array = values;
    t.hash = reinterpret_cast<void*>(0x99a424u);
    // Exhaust every occupancy pattern through size 10, including non-prefix holes.
    for (unsigned n = 0; n <= 10; ++n) {
        t.arraySize = n;
        for (unsigned mask = 0; mask < (1u << n); ++mask) {
            for (unsigned i = 0; i < 16; ++i) {
                values[i].payload = 0xdead0000u + i;
                values[i].tag = (mask & (1u << i)) ? (i % 2 ? 0xffffffffu : 3u) : 0;
            }
            int r = check(t, false, 0);
            if (r) { return 10 + r; }
        }
    }
    // Every contiguous prefix: known answer, and hash pointer must be ignored
    // when a nonempty array's final slot is nil (even an invalid hash pointer).
    for (unsigned n = 1; n <= 16; ++n) {
        for (unsigned prefix = 0; prefix < n; ++prefix) {
            t.arraySize = n;
            t.hash = reinterpret_cast<void*>(1u);
            for (unsigned i = 0; i < 16; ++i) { values[i].tag = i < prefix ? 7u : 0u; }
            int r = check(t, true, prefix);
            if (r) { return 20 + r; }
        }
    }
    // Real hash-helper tail path: next integer exists explicitly as nil,
    // avoiding reliance on the unsubmitted global nil/float-zero fixtures.
    t.hash = nodes;
    t.unknown00[7] = 0; // one bucket, divisor 1
    nodes[0].value.payload = 0x12345678u;
    nodes[0].value.tag = 0;
    nodes[0].keyTag = 3;
    nodes[0].next = 0;
    for (unsigned n = 0; n <= 16; ++n) {
        t.arraySize = n;
        for (unsigned i = 0; i < 16; ++i) { values[i].tag = 1; }
        nodes[0].key = static_cast<float>(n + 1);
        int r = check(t, true, n);
        if (r) { return 30 + r; }
    }
    // Empty array with hash length 1: helper's exponential growth executes.
    t.arraySize = 0;
    t.array = 0; // zero-size path must not dereference array
    nodes[0].key = 1.0f;
    nodes[0].value.tag = 1;
    nodes[0].next = &nodes[1];
    nodes[1].key = 2.0f;
    nodes[1].keyTag = 3;
    nodes[1].value.tag = 0;
    nodes[1].next = 0;
    int r = check(t, true, 1);
    if (r) { return 40 + r; }
    t.hash = reinterpret_cast<void*>(0x99a424u);
    return check(t, true, 0);
}
