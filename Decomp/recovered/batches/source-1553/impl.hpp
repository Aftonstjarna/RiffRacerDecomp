#ifndef WORKER_VIEW_PIVOT_ORDER_HPP
#define WORKER_VIEW_PIVOT_ORDER_HPP
#include <stdint.h>
// Only the observed key is modeled; the preceding bytes belong to the caller.
struct WorkerViewItem { unsigned char opaque[0x188]; int32_t key; };
void worker_view_pivot_order(WorkerViewItem** first, WorkerViewItem** middle, WorkerViewItem** last);
#endif
