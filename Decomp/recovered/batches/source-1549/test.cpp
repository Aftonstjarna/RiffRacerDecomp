#include "impl.hpp"
#include <stdint.h>
extern "C" void __attribute__((fastcall)) original_worker_view_heap_prepare(WorkerViewHeapItem**, WorkerViewHeapItem**);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();

static WorkerViewHeapItem items[96];
static int32_t keys[96];
static WorkerViewHeapItem* a[100];
static WorkerViewHeapItem* b[100];
static unsigned fs_storage[8];
static unsigned state = 0x31a42f11u;
static unsigned random_word() { state = state * 1664525u + 1013904223u; return state; }

extern "C" int test_main() {
    fs_storage[0] = 0x13579bdfu;
    if (test_install_fs(fs_storage) != 0) return 1;
    const unsigned fs_head = test_get_fs_head();
    if (fs_head != 0x13579bdfu) return 2;
    for (int mode = 0; mode < 8; ++mode) {
        for (int n = 0; n <= 96; ++n) {
            for (int i = 0; i < 96; ++i) {
                for (int j = 0; j < 0x188; ++j) items[i].unknown[j] = (unsigned char)(i + j);
                switch (mode) {
                case 0: items[i].key = i; break;
                case 1: items[i].key = -i; break;
                case 2: items[i].key = 7; break;
                case 3: items[i].key = i % 3 - 1; break;
                case 4: items[i].key = (i & 1) ? INT32_MIN : INT32_MAX; break;
                default: items[i].key = (int32_t)random_word(); break;
                }
                keys[i] = items[i].key;
                a[i+2] = b[i+2] = &items[i];
            }
            a[0] = b[0] = &items[95]; a[1] = b[1] = &items[94];
            a[98] = b[98] = &items[93]; a[99] = b[99] = &items[92];
            original_worker_view_heap_prepare(a + 2, a + 2 + n);
            if (test_get_fs_head() != fs_head) return 3;
            worker_view_heap_prepare(b + 2, b + 2 + n);
            for (int i = 0; i < 100; ++i) if (a[i] != b[i]) return 4;
            for (int i = 1; i < n; ++i)
                if (b[2 + (i-1)/2]->key < b[2+i]->key) return 5;
            for (int i = 0; i < 96; ++i) {
                if (items[i].key != keys[i]) return 7;
                for (int j = 0; j < 0x188; ++j)
                    if (items[i].unknown[j] != (unsigned char)(i+j)) return 6;
            }
        }
    }
    return 0;
}
