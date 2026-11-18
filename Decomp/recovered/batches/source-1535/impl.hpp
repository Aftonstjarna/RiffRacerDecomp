#ifndef WORKER_VIEW_SMALL_SORT_HPP
#define WORKER_VIEW_SMALL_SORT_HPP
#include <stdint.h>
// Only the key is identified; the rest of the pointed-to object is opaque.
struct WorkerViewSortItem {
    unsigned char unknown[0x188];
    int32_t sort_key;
};
// Sorts a valid half-open range of pointers; preserves equal-key order.
void worker_view_pointer_small_sort(WorkerViewSortItem** first, WorkerViewSortItem** last);
#endif
