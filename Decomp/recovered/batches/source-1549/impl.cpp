#include "impl.hpp"
#include <stddef.h>

// 0x42c7d0: bottom-up heap construction, using the same downward-then-upward
// adjustment as the original. Equal child keys choose the right-hand child.
void WORKER_FASTCALL worker_view_heap_prepare(WorkerViewHeapItem** first,
                                              WorkerViewHeapItem** last) {
    const ptrdiff_t count = last - first;
    for (ptrdiff_t parent = count / 2; parent > 0;) {
        --parent;
        WorkerViewHeapItem* value = first[parent];
        ptrdiff_t hole = parent;
        ptrdiff_t child = 2 * hole + 2;
        while (child < count) {
            if (first[child]->key < first[child - 1]->key)
                --child;
            first[hole] = first[child];
            hole = child;
            child = 2 * hole + 2;
        }
        if (child == count) {
            first[hole] = first[count - 1];
            hole = count - 1;
        }
        while (hole > parent) {
            ptrdiff_t up = (hole - 1) / 2;
            if (first[up]->key >= value->key)
                break;
            first[hole] = first[up];
            hole = up;
        }
        first[hole] = value;
    }
}
