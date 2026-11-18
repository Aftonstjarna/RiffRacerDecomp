#include "impl.hpp"
// VA 0x43ee20. The caller supplies a valid forward, half-open range.
void VIEW_STDCALL worker_view_pointer_range_destroy(WorkerView** first, WorkerView** last) {
    while (first != last) {
        WorkerView* view = *first++;
        if (view) {
            char* address = reinterpret_cast<char*>(view) + view->table->counted_offset;
            CountedView* counted = reinterpret_cast<CountedView*>(address);
            if (--counted->references == 0)
                counted->table->destroy(counted, 1);
        }
    }
}
