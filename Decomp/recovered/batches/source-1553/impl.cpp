#include "impl.hpp"
#include <stddef.h>

static void order_pair(WorkerViewItem** a, WorkerViewItem** b) {
    if ((*b)->key < (*a)->key) {
        WorkerViewItem* t = *a; *a = *b; *b = t;
    }
}
static void order_three(WorkerViewItem** a, WorkerViewItem** b, WorkerViewItem** c) {
    order_pair(a, b); order_pair(b, c); order_pair(a, b);
}
// VA 0x42c5c0. first and last are inclusive; middle is supplied by caller.
// This is an internal register convention, not a public C++ method ABI.
void worker_view_pivot_order(WorkerViewItem** first, WorkerViewItem** middle, WorkerViewItem** last) {
    ptrdiff_t span = last - first;
    if (span > 40) {
        ptrdiff_t step = (span + 1) / 8;
        order_three(first, first + step, first + 2 * step);
        order_three(middle - step, middle, middle + step);
        order_three(last - 2 * step, last - step, last);
        order_three(first + step, middle, last - step);
    } else {
        order_three(first, middle, last);
    }
}
