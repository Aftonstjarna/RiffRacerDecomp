#include "impl.hpp"
#include <stddef.h>
extern "C" void __attribute__((thiscall)) original_worker_record_reset(WorkerRecord*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
struct Control { void (**vtable)(); uint32_t count; uint32_t marker; };
struct Object { uint32_t marker; int32_t* table; uint32_t padding[2]; Control control; uint32_t tail; };
static WorkerRecord record;
static Object objects[3];
static void* entries[6];
static int32_t offsets[2] = { 123, 12 };
static int calls, bad, order[8];
static bool mutate;
static void __attribute__((thiscall)) release_callback(Control* c, unsigned flag) {
    if (flag != 1 || c->count != 0 || calls >= 8 || record.current_1 != record.start_1 ||
        record.current_2 != record.start_2 || record.current_3 != 0xa5a5a5a5u ||
        record.cleared_5f4 != 0xa5a5a5a5u) bad = 1;
    if (calls < 8) order[calls] = c == &objects[0].control ? 0 : c == &objects[1].control ? 1 : c == &objects[2].control ? 2 : -1;
    ++calls;
    if (mutate) record.references.begin = entries + 1;
}
static void (*vtable[1])() = { reinterpret_cast<void(*)()>(release_callback) };
static unsigned char expected_record[sizeof(record)], expected_objects[sizeof(objects)];
static int expected_calls, expected_order[8];
static void fill(void* p, unsigned n, unsigned char c) { unsigned char* q = static_cast<unsigned char*>(p); while (n--) *q++ = c; }
static void copy(void* d, const void* s, unsigned n) { unsigned char* a = static_cast<unsigned char*>(d); const unsigned char* b = static_cast<const unsigned char*>(s); while (n--) *a++ = *b++; }
static bool same(const void* d, const void* s, unsigned n) { const unsigned char* a = static_cast<const unsigned char*>(d); const unsigned char* b = static_cast<const unsigned char*>(s); while (n--) if (*a++ != *b++) return false; return true; }
static void setup(int scenario) {
    fill(&record, sizeof(record), 0xa5);
    record.start_1 = 0x12345678; record.start_2 = 0x87654321;
    record.start_3 = 3; record.start_4 = 4; record.start_5 = 5; record.start_6 = 6;
    for (int i = 0; i < 3; ++i) {
        fill(&objects[i], sizeof(objects[i]), 0x69);
        objects[i].table = offsets; objects[i].control.vtable = vtable;
        objects[i].control.count = i == 0 ? 2 : i == 1 ? 1 : 0;
    }
    entries[0] = &objects[0]; entries[1] = 0; entries[2] = &objects[1];
    entries[3] = &objects[0]; entries[4] = &objects[2]; entries[5] = &objects[1];
    record.references.begin = entries; record.references.end = entries + (scenario == 0 ? 0 : scenario == 2 ? 3 : 5);
    record.references.capacity_end = entries + 6;
    calls = bad = 0; for (int i = 0; i < 8; ++i) order[i] = -1;
    mutate = scenario == 2;
}
static int run(int scenario) {
    setup(scenario);
    unsigned head = test_get_fs_head();
    original_worker_record_reset(&record);
    if (test_get_fs_head() != head || bad) return 1;
    if (record.references.end != record.references.begin || record.references.capacity_end != entries + 6 ||
        record.current_1 != record.start_1 || record.current_2 != record.start_2 ||
        record.current_3 != 3 || record.current_4 != 4 || record.current_5 != 5 || record.current_6 != 6 ||
        record.value_5f0 != 0x3f800000u || record.cleared_5f4 || record.cleared_5f8 || record.value_600 != 0x80 ||
        record.cleared_28c[0] || record.cleared_28c[1] || record.cleared_28c[2] || record.cleared_28c[3] || record.cleared_29c) return 2;
    if ((scenario == 0 && calls != 0) || (scenario == 1 && (calls != 2 || order[0] != 1 || order[1] != 0 || objects[2].control.count != 0xffffffffu)) ||
        (scenario == 2 && (calls != 1 || order[0] != 1 || record.references.begin != entries + 1))) return 3;
    copy(expected_record, &record, sizeof(record)); copy(expected_objects, objects, sizeof(objects));
    expected_calls = calls; for (int i = 0; i < 8; ++i) expected_order[i] = order[i];
    setup(scenario); record.reset();
    if (test_get_fs_head() != head || bad || calls != expected_calls || !same(order, expected_order, sizeof(order)) ||
        !same(&record, expected_record, sizeof(record)) || !same(objects, expected_objects, sizeof(objects)) ||
        entries[0] != &objects[0] || entries[1] != 0 || entries[2] != &objects[1] || entries[3] != &objects[0] || entries[4] != &objects[2] || entries[5] != &objects[1]) return 4;
    return 0;
}
extern "C" int test_main() {
    uint32_t fs[8] = { 0x12345678 };
    if (sizeof(void*) != 4 || offsetof(WorkerRecord, references) != 0x34 || offsetof(WorkerRecord, cleared_28c) != 0x28c || offsetof(WorkerRecord, value_5f0) != 0x5f0 || offsetof(WorkerRecord, value_600) != 0x600) return 1;
    if (test_install_fs(fs) != 0 || test_get_fs_head() != 0x12345678) return 2;
    for (int i = 0; i < 3; ++i) { int r = run(i); if (r) return 10 + i * 4 + r; }
    return 0;
}
