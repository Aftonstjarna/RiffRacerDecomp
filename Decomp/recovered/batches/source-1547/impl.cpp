#include "impl.hpp"

// VA 0x42c9d0: ECX=heap, EDX=hole; length, value slot and an
// unused context word are caller-cleaned stack arguments. The caller at
// 0x42c8c0 uses this to restore a heap after removing its root.
void worker_view_heap_sift(WorkerViewHeapItem** heap, int32_t hole,
                           int32_t length, WorkerViewHeapItem* const* value) {
    const int32_t top = hole;
    int32_t child = hole * 2 + 2;
    while (child < length) {
        if (heap[child]->priority < heap[child - 1]->priority)
            --child;
        heap[hole] = heap[child];
        hole = child;
        child = hole * 2 + 2;
    }
    if (child == length) {
        heap[hole] = heap[length - 1];
        hole = length - 1;
    }
    // The helper at 0x42ca50 reloads *value after every move: the slot
    // can alias the heap, so caching the pointer changes observable behavior.
    while (hole > top) {
        int32_t parent = (hole - 1) / 2;
        if (heap[parent]->priority >= (*value)->priority) break;
        heap[hole] = heap[parent];
        hole = parent;
    }
    heap[hole] = *value;
}
