#include "impl.hpp"
#include <stdint.h>
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
// The original uses ECX, EDX and a caller-cleaned stack argument. GCC's
// fastcall puts arguments in those locations, but assumes callee stack cleanup.
// Isolate each call in a frame whose epilogue restores ESP from EBP.
extern "C" void __attribute__((fastcall)) original_worker_view_pivot_order(WorkerViewItem**, WorkerViewItem**, WorkerViewItem**);
__attribute__((noinline)) static void call_original(WorkerViewItem** a, WorkerViewItem** b, WorkerViewItem** c) {
    original_worker_view_pivot_order(a,b,c);
}
static WorkerViewItem items[160];
static int32_t saved_keys[160];
static WorkerViewItem* expected[160];
static WorkerViewItem* actual[160];
static unsigned fs_storage[16];
static uint32_t random_state = 0x12345678u;
static uint32_t next_random() { random_state = random_state * 1664525u + 1013904223u; return random_state; }
extern "C" int test_main() {
    fs_storage[0] = 0x13579bdfu;
    if (test_install_fs(fs_storage) != 0) return 1;
    for (int n = 1; n <= 120; ++n) {
        for (int mode = 0; mode < 12; ++mode) {
            for (int i = 0; i < 160; ++i) {
                for (int j = 0; j < 0x188; ++j) items[i].opaque[j] = (unsigned char)(i+j);
                uint32_t v = next_random();
                if (mode == 0) v = (uint32_t)i;
                if (mode == 1) v = (uint32_t)(160-i);
                if (mode == 2) v = 7;
                if (mode == 3) v %= 3;
                if (mode == 4) v = (i & 1) ? 0x80000000u : 0x7fffffffu;
                items[i].key = (int32_t)v;
                saved_keys[i] = items[i].key;
                expected[i] = actual[i] = &items[i];
            }
            int first = 4, last = first + n - 1, middle = first + (n-1)/2;
            call_original(expected+first, expected+middle, expected+last);
            if (test_get_fs_head() != 0x13579bdfu) return 2;
            worker_view_pivot_order(actual+first, actual+middle, actual+last);
            for (int i = 0; i < 160; ++i) {
                if (actual[i] != expected[i]) return 3;
                if (items[i].key != saved_keys[i]) return 5;
                for (int j = 0; j < 0x188; ++j)
                    if (items[i].opaque[j] != (unsigned char)(i+j)) return 4;
            }
        }
    }
    return 0;
}
