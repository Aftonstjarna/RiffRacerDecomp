#include "impl.hpp"
// 0x42ca50: internal optimized ABI uses ECX for heap and EDX for hole;
// top and value are stack arguments, followed by a caller-supplied unused word.
void worker_view_heap_push(WorkerViewHeapItem** heap, int32_t hole,
                           int32_t top, WorkerViewHeapItem* const* value) {
    while (top < hole) {
        int32_t parent = (hole - 1) / 2;
        WorkerViewHeapItem* parent_item = heap[parent];
        if (parent_item->priority >= (*value)->priority)
            break;
        heap[hole] = parent_item;
        hole = parent;
    }
    heap[hole] = *value;
}
