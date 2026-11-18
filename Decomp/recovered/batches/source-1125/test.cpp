#include "impl.hpp"
extern "C" void WORKER_THISCALL original_worker_record_range_clear(WorkerRecordRange*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs_storage[8];

static int calls, bad, change_begin;
static WorkerReleaseOwner* seen[8];
static WorkerRecordRange* active_range;
static WorkerRecord* replacement;
static void WORKER_THISCALL release_callback(WorkerReleaseOwner* owner, int flag) {
    if (flag != 1 || owner->references != 0 || calls >= 8) ++bad;
    if (calls < 8) seen[calls] = owner;
    ++calls;
    if (change_begin) { active_range->begin = replacement; active_range->end = replacement; }
}
struct Fixture {
    WorkerOwnerTable owner_table;
    WorkerObjectTable object_table;
    struct Pair { WorkerObject object; uint32_t gap; WorkerReleaseOwner owner; } pair[4];
    WorkerRecord records[6];
    WorkerRecordRange range;
};
static void init(Fixture& f) {
    f.owner_table.release = release_callback;
    f.object_table.unknown = 0x12345678;
    f.object_table.owner_offset = 8;
    for (int i=0;i<4;++i) {
        f.pair[i].object.table = &f.object_table;
        f.pair[i].gap = 0x33445566;
        f.pair[i].owner.table = &f.owner_table;
        f.pair[i].owner.references = i == 0 ? 1 : (i == 1 ? 2 : (i == 2 ? 0 : 1));
    }
    for (int i=0;i<6;++i) {
        f.records[i].object = 0;
        for (int j=0;j<5;++j) f.records[i].payload[j] = 0xabc00000u + i*16+j;
    }
    f.records[0].object = &f.pair[0].object;
    f.records[1].object = 0;
    f.records[2].object = &f.pair[1].object;
    f.records[3].object = &f.pair[1].object;
    f.records[4].object = &f.pair[2].object;
    f.records[5].object = &f.pair[3].object;
    f.range.begin = f.records;
    f.range.end = f.records+6;
}
static int run(bool original, int mode) {
    Fixture f; init(f); calls=0; bad=0; change_begin = mode == 2;
    active_range=&f.range; replacement=f.records+1;
    if (mode == 1) f.range.end=f.range.begin;
    if (original) {
        original_worker_record_range_clear(&f.range);
        if (test_get_fs_head() != 0x1234abcdu) return 7;
    } else f.range.clear();
    if (bad || f.range.begin != (mode == 2 ? f.records+1 : f.records) || f.range.end != f.range.begin) return 1;
    int expected_calls = mode == 1 ? 0 : 3;
    if (calls != expected_calls) return 2;
    if (mode != 1 && (seen[0] != &f.pair[0].owner || seen[1] != &f.pair[1].owner || seen[2] != &f.pair[3].owner)) return 3;
    const uint32_t initial[4] = {1,2,0,1};
    const uint32_t final[4] = {0,0,0xffffffffu,0};
    for (int i=0;i<4;++i) {
        if (f.pair[i].owner.references != (mode == 1 ? initial[i] : final[i]) || f.pair[i].gap != 0x33445566 || f.pair[i].object.table != &f.object_table || f.pair[i].owner.table != &f.owner_table) return 4;
    }
    for (int i=0;i<6;++i) for (int j=0;j<5;++j)
        if (f.records[i].payload[j] != 0xabc00000u + i*16+j) return 5;
    if (f.records[0].object != &f.pair[0].object || f.records[1].object != 0 || f.records[2].object != &f.pair[1].object || f.records[3].object != &f.pair[1].object || f.records[4].object != &f.pair[2].object || f.records[5].object != &f.pair[3].object || f.object_table.unknown != 0x12345678 || f.object_table.owner_offset != 8) return 6;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0] = 0x1234abcdu;
    if (test_install_fs(fs_storage) != 0) return 100;
    for (int i=0;i<3;++i) { int a=run(false,i), b=run(true,i); if (a || b) return 10*i + (a ? a : b); }
    return 0;
}
