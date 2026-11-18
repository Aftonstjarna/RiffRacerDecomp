#ifndef WORKER_VIEW_HEAP_FINISH_HPP
#define WORKER_VIEW_HEAP_FINISH_HPP
#include <stdint.h>
struct WorkerViewHeapItem {
    unsigned char unknown[0x188];
    int32_t priority;
};
// Range is a valid, aligned array of pointers; the caller supplies a max heap.
// The third argument is forwarded by the original helpers but never inspected.
void worker_view_heap_finish(WorkerViewHeapItem** first, WorkerViewHeapItem** last, uintptr_t context);
#endif
