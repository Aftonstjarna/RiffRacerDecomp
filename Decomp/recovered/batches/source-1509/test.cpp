#include "impl.hpp"
#include <stdint.h>
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
// ECX, EDX, then a stack argument. The original uses caller cleanup; GCC's
// fastcall assumes callee cleanup. This isolated noinline adapter has a frame
// pointer, which restores the stack on return, and makes only this one call.
extern "C" WorkerRefObject** __attribute__((fastcall)) original_worker_ref_pointer_range_copy(
    WorkerRefObject* const*, WorkerRefObject* const*, WorkerRefObject**);
static __attribute__((noinline)) WorkerRefObject** oracle(WorkerRefObject* const* a,
    WorkerRefObject* const* b, WorkerRefObject** c) {
    return original_worker_ref_pointer_range_copy(a, b, c);
}
struct Object { WorkerRefObject object; uint32_t guard; uint32_t count; uint32_t other; };
static int check(bool b) { return b ? 0 : 1; }
extern "C" int test_main() {
    uint32_t fs[8] = {0x12345678};
    if (test_install_fs(fs) != 0) return 1;
    unsigned head = test_get_fs_head();
    WorkerRefMetadata meta = {0xaabbccdd, 4};
    Object a = {{&meta}, 0x1234, 7, 0x5678};
    Object b = {{&meta}, 0x1234, 7, 0x5678};
    WorkerRefObject* src1[] = {&a.object, 0, &a.object};
    WorkerRefObject* src2[] = {&b.object, 0, &b.object};
    WorkerRefObject* out1[] = {0, &a.object, 0, &a.object};
    WorkerRefObject* out2[] = {0, &b.object, 0, &b.object};
    WorkerRefObject** r1 = worker_ref_pointer_range_copy(src1, src1 + 3, out1);
    WorkerRefObject** r2 = oracle(src2, src2 + 3, out2);
    int fail = check(test_get_fs_head() == head);
    fail |= check(r1 == out1 + 3 && r2 == out2 + 3);
    fail |= check(out1[0] == &a.object && out2[0] == &b.object && !out1[1] && !out2[1]);
    fail |= check(out1[2] == &a.object && out2[2] == &b.object && out1[3] == &a.object && out2[3] == &b.object);
    fail |= check(a.count == 9 && b.count == 9 && a.guard == 0x1234 && b.guard == 0x1234 && a.other == 0x5678 && b.other == 0x5678);
    r1 = worker_ref_pointer_range_copy(src1, src1, out1);
    r2 = oracle(src2, src2, out2);
    fail |= check(test_get_fs_head() == head && r1 == out1 && r2 == out2 && a.count == 9 && b.count == 9);
    r1 = worker_ref_pointer_range_copy(src1, src1 + 1, 0);
    r2 = oracle(src2, src2 + 1, 0);
    fail |= check(test_get_fs_head() == head && reinterpret_cast<uintptr_t>(r1) == 4 && reinterpret_cast<uintptr_t>(r2) == 4 && a.count == 9 && b.count == 9);
    // Forward overlap observes the preceding write, and increments twice.
    WorkerRefObject* overlap1[] = {&a.object, 0, 0};
    WorkerRefObject* overlap2[] = {&b.object, 0, 0};
    a.count = b.count = 0xffffffffu;
    r1 = worker_ref_pointer_range_copy(overlap1, overlap1 + 2, overlap1 + 1);
    r2 = oracle(overlap2, overlap2 + 2, overlap2 + 1);
    fail |= check(test_get_fs_head() == head && r1 == overlap1 + 3 && r2 == overlap2 + 3);
    fail |= check(overlap1[2] == &a.object && overlap2[2] == &b.object && a.count == 1 && b.count == 1);
    return fail;
}
