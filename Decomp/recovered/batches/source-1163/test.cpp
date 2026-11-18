#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_worker_reference_range_clear(WorkerReferenceRange*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();

struct Control { void (**vtable)(); uint32_t count; uint32_t marker; };
struct Object { uint32_t marker; int32_t* table; uint32_t padding[2]; Control control; uint32_t tail; };
static int calls, bad;
static Control* seen[8];
static WorkerReferenceRange* mutate_range;
static void** new_begin;
static void __attribute__((thiscall)) release_callback(Control* c, unsigned flag) {
    if (flag != 1 || c->count != 0 || calls >= 8) bad = 1;
    if (calls < 8) seen[calls] = c;
    ++calls;
    if (mutate_range) mutate_range->begin = new_begin;
}
static void (*vtable[1])() = { reinterpret_cast<void(*)()>(release_callback) };
static int32_t offsets[2] = { 0x1234, 12 };
static void init(Object& o, uint32_t count) {
    o.marker = 0x11223344; o.table = offsets; o.padding[0] = 0x55667788;
    o.padding[1] = 0x99887766; o.control.vtable = vtable;
    o.control.count = count; o.control.marker = 0xabcdef01; o.tail = 0xdeadbeef;
}
static int intact(const Object& o) {
    return o.marker == 0x11223344 && o.table == offsets &&
      o.padding[0] == 0x55667788 && o.padding[1] == 0x99887766 &&
      o.control.vtable == vtable && o.control.marker == 0xabcdef01 && o.tail == 0xdeadbeef;
}
static int run(bool original, int scenario) {
    Object a, b, c; init(a, 2); init(b, 1); init(c, 0);
    void* entries[6] = { &a, 0, &b, &a, &c, &b };
    WorkerReferenceRange range = { entries, entries + 5, entries + 6 };
    if (scenario == 0) range.end = range.begin;
    if (scenario == 2) { range.end = entries + 3; mutate_range = &range; new_begin = entries + 1; }
    else mutate_range = 0;
    calls = bad = 0; for (int i = 0; i < 8; ++i) seen[i] = 0;
    unsigned fs = test_get_fs_head();
    if (original) original_worker_reference_range_clear(&range); else range.clear();
    if (test_get_fs_head() != fs || bad || range.end != range.begin || range.capacity_end != entries + 6 ||
        !intact(a) || !intact(b) || !intact(c) || entries[0] != &a || entries[1] != 0 ||
        entries[2] != &b || entries[3] != &a || entries[4] != &c || entries[5] != &b) return 1;
    if (scenario == 0) return calls != 0 || a.control.count != 2 || b.control.count != 1 || c.control.count != 0;
    if (scenario == 1) return calls != 2 || seen[0] != &b.control || seen[1] != &a.control || a.control.count != 0 || b.control.count != 0 || c.control.count != 0xffffffffu;
    return calls != 1 || seen[0] != &b.control || a.control.count != 1 || b.control.count != 0 || c.control.count != 0 || range.begin != entries + 1;
}
extern "C" int test_main() {
    uint32_t fs_storage[8] = { 0x12345678 };
    if (test_install_fs(fs_storage) != 0 || test_get_fs_head() != 0x12345678) return 1;
    for (int i = 0; i < 3; ++i) if (run(true, i) || run(false, i)) return 2 + i;
    return 0;
}
