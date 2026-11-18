#include "impl.hpp"

// 0x42c8c0. Internal original ABI: ECX=first, EDX=last, stack=context.
// The caller at 0x42c3f1 first constructs a max heap over this range.
void worker_view_heap_finish(WorkerViewHeapItem** first, WorkerViewHeapItem** last, uintptr_t context) {
    (void)context;
    while (last - first > 1) {
        --last;
        WorkerViewHeapItem* value = *last;
        *last = *first;
        int32_t length = static_cast<int32_t>(last - first);
        int32_t hole = 0;
        int32_t child = 2;
        // 0x42c9d0 selects the right child on equal priorities.
        while (child < length) {
            if (first[child]->priority < first[child - 1]->priority)
                --child;
            first[hole] = first[child];
            hole = child;
            child = hole * 2 + 2;
        }
        if (child == length) {
            first[hole] = first[length - 1];
            hole = length - 1;
        }
        // 0x42ca50 restores the saved value, stopping on equality.
        while (hole > 0) {
            int32_t parent = (hole - 1) / 2;
            if (first[parent]->priority >= value->priority) break;
            first[hole] = first[parent];
            hole = parent;
        }
        first[hole] = value;
    }
}
