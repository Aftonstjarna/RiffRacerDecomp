#include "impl.hpp"
#include <stddef.h>
extern "C" void* memcpy(void* d, const void* s, size_t n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    const unsigned char* b = static_cast<const unsigned char*>(s);
    for (size_t i = 0; i < n; ++i) { a[i] = b[i]; }
    return d;
}
extern "C" void* memset(void* d, int c, size_t n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    for (size_t i = 0; i < n; ++i) { a[i] = static_cast<unsigned char>(c); }
    return d;
}
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x = static_cast<const unsigned char*>(a);
    const unsigned char* y = static_cast<const unsigned char*>(b);
    for (unsigned i = 0; i < n; ++i) { if (x[i] != y[i]) { return false; } }
    return true;
}
extern "C" WideString* __attribute__((thiscall)) original_wide_erase(WideString*, uint32_t, uint32_t);
static bool imports_mapped;
extern "C" void test_write(const char*, unsigned);
static void* jump_state[5];
static const char* error_message;
extern "C" void wide_out_of_range(const char* p) {
    error_message = p;
    __builtin_longjmp(jump_state, 1);
}
extern "C" void* oracle_move(void* d, const void* s, unsigned n) {
    // Erase always moves left within the same buffer.
    return memcpy(d, s, n);
}
// Test-only import table. Used only if the linker actually places it at the IAT.
// Ordinary trusted linking may leave it elsewhere; never call unmapped imports.
extern "C" {
__attribute__((section(".oracle_iat"), aligned(4))) void* oracle_iat[207];
}
static int run_case(unsigned capacity, unsigned length, unsigned offset, unsigned count) {
    struct Guarded { unsigned before; WideString value; unsigned after; } a, b, expected;
    uint16_t ha[80], hb[80], he[80];
    memset(&a, 0xa7, sizeof(a));
    memset(ha, 0x83, sizeof(ha));
    a.value.size = length;
    a.value.capacity = capacity;
    uint16_t* data = capacity >= 8 ? reinterpret_cast<uint16_t*>(ha + 8) : a.value.storage.local;
    for (unsigned i = 0; i < length; ++i) { data[i] = static_cast<uint16_t>((i * 977) & 65535); }
    // Deliberately nonzero old terminator detects whether count=0 writes it.
    data[length] = 0x61;
    memcpy(&b, &a, sizeof(a));
    memcpy(hb, ha, sizeof(ha));
    if (capacity >= 8) {
        a.value.storage.heap = reinterpret_cast<uint16_t*>(ha + 8);
        b.value.storage.heap = reinterpret_cast<uint16_t*>(hb + 8);
    }
    memcpy(&expected, &a, sizeof(a));
    memcpy(he, ha, sizeof(ha));
    unsigned removed = count < length - offset ? count : length - offset;
    uint16_t* ed = capacity >= 8 ? reinterpret_cast<uint16_t*>(he + 8) : expected.value.storage.local;
    if (removed != 0 || offset == length) {
        for (unsigned i = offset; i < length - removed; ++i) { ed[i] = ed[i + removed]; }
        expected.value.size = length - removed;
        ed[length - removed] = 0;
    }
    if (a.value.erase(offset, count) != &a.value) { return 1; }
    if (imports_mapped || count == 0 || count >= length - offset) {
        if (original_wide_erase(&b.value, offset, count) != &b.value) { return 2; }
    } else {
        // Missing external CRT IAT: retain independent expected-state checks.
        // No original call: compare recovered output with independent expected state.
        memcpy(&b, &expected, sizeof(b));
        memcpy(hb, he, sizeof(hb));
        if (capacity >= 8) { b.value.storage.heap = hb + 8; }
    }
    if (capacity >= 8) {
        if (b.value.storage.heap != reinterpret_cast<uint16_t*>(hb + 8)) { return 3; }
        b.value.storage.heap = a.value.storage.heap;
    }
    if (!equal(&a, &b, sizeof(a)) || !equal(&a, &expected, sizeof(a))) { return 4; }
    if (!equal(ha, hb, sizeof(ha)) || !equal(ha, he, sizeof(ha))) { return 5; }
    return 0;
}
static int invalid_case(bool original, unsigned offset) {
    WideString s, before;
    memset(&s, 0x52, sizeof(s));
    s.size = 3; s.capacity = 7;
    memcpy(&before, &s, sizeof(s));
    error_message = 0;
    if (__builtin_setjmp(jump_state) == 0) {
        if (original) { original_wide_erase(&s, offset, 0); }
        else { s.erase(offset, 0); }
        return 6;
    }
    if (!equal(&s, &before, sizeof(s))) { return 7; }
    if (original) {
        if (reinterpret_cast<size_t>(error_message) != 0x99995c) { return 8; }
    } else {
        const char text[] = "invalid string position";
        if (!equal(error_message, text, sizeof(text))) { return 9; }
    }
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(WideString) == 24, "original i386 layout");
    imports_mapped = reinterpret_cast<size_t>(oracle_iat) == 0x92d16c;
    oracle_iat[0] = reinterpret_cast<void*>(&wide_out_of_range);
    oracle_iat[206] = reinterpret_cast<void*>(&oracle_move);
    const unsigned capacities[] = {0, 7, 8, 31, 0xffffffffu};
    for (unsigned c = 0; c < 5; ++c) {
        unsigned max_length = capacities[c] < 8 ? 7 : 63;
        for (unsigned n = 0; n <= max_length; ++n) {
            for (unsigned off = 0; off <= n; ++off) {
                for (unsigned count = 0; count <= n + 1; ++count) {
                    int r = run_case(capacities[c], n, off, count);
                    if (r) { return r; }
                }
                int r = run_case(capacities[c], n, off, 0xffffffffu);
                if (r) { return r; }
            }
        }
    }
    for (unsigned i = 0; i < 2; ++i) {
        if (i != 0 && !imports_mapped) { continue; }
        int r = invalid_case(i != 0, 4);
        if (r) { return r; }
        r = invalid_case(i != 0, 0xffffffffu);
        if (r) { return r; }
    }
    if (imports_mapped) {
        const char msg[] = "PASS: all original comparisons, intercepted CRT imports.\n";
        test_write(msg, sizeof(msg)-1);
    } else {
        const char msg[] = "PASS: original suffix/no-op comparisons; shift/error original paths require IAT mapping at 0x92d16c.\n";
        test_write(msg, sizeof(msg)-1);
    }
    return 0;
}
