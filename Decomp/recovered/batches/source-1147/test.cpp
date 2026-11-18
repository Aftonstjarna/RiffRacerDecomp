#include "impl.hpp"
#include <stddef.h>
extern "C" void __attribute__((thiscall)) original_worker_slot_reset(WorkerSlot*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();

static unsigned fs_storage[16];
static unsigned char actual[sizeof(WorkerSlot) + 16];
static unsigned char expected[sizeof(WorkerSlot) + 16];

extern "C" int test_main() {
    if (sizeof(WorkerSlot) != 0x1ac || offsetof(WorkerSlot, tail_19c) != 0x19c) return 1;
    fs_storage[0] = 0x12345678u;
    if (test_install_fs(fs_storage) != 0) return 2;
    const unsigned fs_head = test_get_fs_head();
    for (unsigned scenario = 0; scenario != 6; ++scenario) {
        for (unsigned i = 0; i != sizeof(actual); ++i) {
            unsigned char v = scenario == 0 ? 0 : scenario == 1 ? 255 :
                (unsigned char)(i * (scenario * 14 + 3) + scenario * 31);
            actual[i] = expected[i] = v;
        }
        WorkerSlot* a = reinterpret_cast<WorkerSlot*>(actual + 8);
        WorkerSlot* e = reinterpret_cast<WorkerSlot*>(expected + 8);
        a->reset();
        original_worker_slot_reset(e);
        if (test_get_fs_head() != fs_head) return 3;
        for (unsigned i = 0; i != sizeof(actual); ++i)
            if (actual[i] != expected[i]) return 4;
        // A second reset is idempotent and must preserve every untouched byte.
        a->reset();
        original_worker_slot_reset(e);
        if (test_get_fs_head() != fs_head) return 5;
        for (unsigned i = 0; i != sizeof(actual); ++i)
            if (actual[i] != expected[i]) return 6;
    }
    return 0;
}
