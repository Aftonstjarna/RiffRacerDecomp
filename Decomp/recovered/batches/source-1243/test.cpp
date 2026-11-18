#include "impl.hpp"
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void __attribute__((thiscall)) original_worker_queue_record_dispatch(void*, uint32_t, const char*, uint32_t, uint32_t);
extern "C" void __attribute__((thiscall)) original_record12_vector_append(RecordVector*, const QueueRecord*);
extern "C" void* copy_callback(void* dst, const void* src, unsigned size) {
    unsigned char* d = static_cast<unsigned char*>(dst);
    const unsigned char* s = static_cast<const unsigned char*>(src);
    for (unsigned i = 0; i < size; ++i) { d[i] = s[i]; }
    return dst;
}
extern "C" {
__attribute__((section(".test_iat"),used,aligned(4))) void* (*test_iat)(void*,const void*,unsigned) = copy_callback;
}
static bool append_fs_ok = true;
void append_queue_record(RecordVector* v, const QueueRecord* r) {
    unsigned before = test_get_fs_head();
    original_record12_vector_append(v, r);
    if (test_get_fs_head() != before) append_fs_ok = false;
}
static unsigned char objects[2][0x2d00] __attribute__((aligned(16)));
static char buffers[2][3][128];
static QueueRecord records[2][3][8];
static uint32_t fs_storage[16];
static bool same(const unsigned char* a, const unsigned char* b, unsigned n) {
    for (unsigned i = 0; i < n; ++i) { if (a[i] != b[i]) return false; }
    return true;
}
static void setup(unsigned side, unsigned buffer_index, unsigned vector_index, unsigned used, bool disabled) {
    unsigned char* p = objects[side];
    for (unsigned i = 0; i < sizeof(objects[side]); ++i) p[i] = 0x5a;
    for (unsigned i = 0; i < sizeof(buffers[side]); ++i) reinterpret_cast<unsigned char*>(buffers[side])[i] = 0xa5;
    for (unsigned i = 0; i < sizeof(records[side]); ++i) reinterpret_cast<unsigned char*>(records[side])[i] = 0x6c;
    p[0xd1] = disabled ? 7 : 0;
    *reinterpret_cast<uint32_t*>(p + 0x2cd8) = buffer_index;
    for (unsigned i = 0; i < 3; ++i) {
        TextBuffer* b = reinterpret_cast<TextBuffer*>(p + 0x2c9c + i * 12);
        b->data = buffers[side][i]; b->used = used; b->unknown = 0x87654321;
        RecordVector* v = reinterpret_cast<RecordVector*>(p + 0x78 + i * 12);
        v->begin = records[side][i]; v->end = records[side][i] + 2; v->capacity_end = records[side][i] + 8;
    }
    (void)vector_index;
}
static int run_case(unsigned bi, unsigned vi, unsigned used, bool disabled, const char* str) {
    setup(0, bi, vi, used, disabled); setup(1, bi, vi, used, disabled);
    unsigned before = test_get_fs_head();
    original_worker_queue_record_dispatch(objects[0], 0x12345678, str, 0xfedcba98, vi);
    if (test_get_fs_head() != before || !append_fs_ok) return 1;
    reinterpret_cast<WorkerQueueOwner*>(objects[1])->dispatch(0x12345678, str, 0xfedcba98, vi);
    if (!append_fs_ok) return 8;
    // Normalize pointer fields before comparing the entire object and record storage.
    for (unsigned i = 0; i < 3; ++i) {
        TextBuffer* a = reinterpret_cast<TextBuffer*>(objects[0] + 0x2c9c + i * 12);
        TextBuffer* b = reinterpret_cast<TextBuffer*>(objects[1] + 0x2c9c + i * 12);
        if (a->used != b->used || a->unknown != b->unknown) return 2;
        a->data = b->data;
        RecordVector* x = reinterpret_cast<RecordVector*>(objects[0] + 0x78 + i * 12);
        RecordVector* y = reinterpret_cast<RecordVector*>(objects[1] + 0x78 + i * 12);
        if (x->end - x->begin != y->end - y->begin || x->capacity_end - x->begin != y->capacity_end - y->begin) return 3;
        x->begin = y->begin; x->end = y->end; x->capacity_end = y->capacity_end;
    }
    if (!disabled) {
        QueueRecord* a = &records[0][vi][2]; QueueRecord* b = &records[1][vi][2];
        if (a->text != buffers[0][bi] + used || b->text != buffers[1][bi] + used) return 4;
        a->text = b->text;
    }
    if (!same(objects[0], objects[1], sizeof(objects[0]))) return 5;
    if (!same(reinterpret_cast<unsigned char*>(buffers[0]), reinterpret_cast<unsigned char*>(buffers[1]), sizeof(buffers[0]))) return 6;
    if (!same(reinterpret_cast<unsigned char*>(records[0]), reinterpret_cast<unsigned char*>(records[1]), sizeof(records[0]))) return 7;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0] = 0xffffffffu;
    if (test_install_fs(fs_storage) != 0) return 10;
    if (run_case(0, 0, 0, false, "")) return 11;
    if (run_case(2, 1, 7, false, "hello")) return 12;
    if (run_case(1, 2, 33, false, "a longer test string")) return 13;
    if (run_case(2, 0, 5, true, static_cast<const char*>(0))) return 14;
    return 0;
}
