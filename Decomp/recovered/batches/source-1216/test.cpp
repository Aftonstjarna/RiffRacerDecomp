#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_worker_byte_vector_ensure_spare(WorkerByteVector*, uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs_storage[16];
static unsigned realloc_calls, error_calls;
static uint32_t requested;
static WorkerByteVector* receiver;
void WORKER_THISCALL WorkerByteVector::reallocate(uint32_t n) {
    ++realloc_calls; requested = n; receiver = this;
}
extern "C" void worker_byte_vector_length_error(const char* message) { ++error_calls; const char expected[] = "vector<T> too long"; for (unsigned i=0; i<sizeof(expected); ++i) if (message[i]!=expected[i]) { error_calls += 100; break; } }
static unsigned char* addr(uint32_t n) { return (unsigned char*)(uintptr_t)n; }
struct Guarded { uint32_t before; WorkerByteVector vector; uint32_t after; };
extern "C" int test_main() {
    fs_storage[0] = 0x12345678;
    if (test_install_fs(fs_storage) != 0) return 1;
    const unsigned head = test_get_fs_head();
    if (head != fs_storage[0]) return 2;
    // No dereferences occur on the no-growth path, including wrapped addresses.
    const uint32_t bases[] = {0, 1, 0x1000, 0x7ffffff0u, 0xfffffff0u};
    const uint32_t spaces[] = {0, 1, 2, 15, 0x7fffffffu, 0xffffffffu};
    for (unsigned b=0; b<5; ++b) for (unsigned s=0; s<6; ++s) {
        uint32_t end = bases[b] + 9u, limit = end + spaces[s];
        uint32_t counts[] = {0, spaces[s], spaces[s] ? spaces[s]-1u : 0u};
        for (unsigned c=0; c<3; ++c) {
            Guarded a = {0x11223344u, {addr(bases[b]), addr(end), addr(limit)}, 0xaabbccddu};
            Guarded o = a;
            realloc_calls = error_calls = 0;
            a.vector.ensure_spare(counts[c]);
            original_worker_byte_vector_ensure_spare(&o.vector, counts[c]);
            if (test_get_fs_head()!=head) return 3;
            if (realloc_calls || error_calls || a.before!=o.before || a.after!=o.after ||
                a.vector.first!=o.vector.first || a.vector.last!=o.vector.last ||
                a.vector.capacity_end!=o.vector.capacity_end) return 4;
        }
    }
    // Growth dependency spy: ordinary geometric growth, requested minimum,
    // arithmetic wrap and the non-returning error hook's observed invocation.
    struct Case { uint32_t begin, end, limit, count, capacity; unsigned errors; };
    const Case cases[] = {
        {0x1000,0x100a,0x1014,11,30,0},
        {0x1000,0x100a,0x1014,40,50,0},
        {0,0,0,1,1,0},
        {0,0xfffffffeu,0xffffffffu,2,0,1},
        {0,0xeffffffeu,0xefffffffu,2,0xf0000000u,0},
        {0x1000,0x1000,0x1000,0xffffffffu,0xffffffffu,0}
    };
    for (unsigned i=0; i<sizeof(cases)/sizeof(cases[0]); ++i) {
        const Case& c=cases[i];
        Guarded a={0x1234abcd,{addr(c.begin),addr(c.end),addr(c.limit)},0x87654321};
        realloc_calls=error_calls=0; requested=0; receiver=0;
        a.vector.ensure_spare(c.count);
        if (realloc_calls!=1 || error_calls!=c.errors || requested!=c.capacity || receiver!=&a.vector ||
            a.before!=0x1234abcdu || a.after!=0x87654321u ||
            a.vector.first!=addr(c.begin) || a.vector.last!=addr(c.end) || a.vector.capacity_end!=addr(c.limit)) return 5+i;
    }
    return 0;
}
