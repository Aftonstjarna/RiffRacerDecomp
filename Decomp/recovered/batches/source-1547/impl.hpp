#ifndef WORKER_VIEW_HEAP_SIFT_HPP
#define WORKER_VIEW_HEAP_SIFT_HPP
#include <stdint.h>
struct WorkerViewHeapItem {
    unsigned char opaque[0x188];
    int32_t priority;
};
// value points to a pointer slot and may alias the heap.
void worker_view_heap_sift(WorkerViewHeapItem** heap, int32_t hole,
                           int32_t length, WorkerViewHeapItem* const* value);
#endif
