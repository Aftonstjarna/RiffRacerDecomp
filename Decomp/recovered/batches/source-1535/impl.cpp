#include "impl.hpp"

void worker_view_pointer_small_sort(WorkerViewSortItem** first, WorkerViewSortItem** last) {
    if (first == last) return;
    for (WorkerViewSortItem** current = first + 1; current != last; ++current) {
        WorkerViewSortItem* item = *current;
        WorkerViewSortItem** hole = current;
        while (hole != first && item->sort_key < (*(hole - 1))->sort_key) {
            *hole = *(hole - 1);
            --hole;
        }
        *hole = item;
    }
}
