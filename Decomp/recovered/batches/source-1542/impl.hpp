#ifndef RIFF_WORKER_VIEW_HEAP_HPP
#define RIFF_WORKER_VIEW_HEAP_HPP
#include <stdint.h>
// Only the signed ordering field is identified; the preceding bytes are opaque.
struct WorkerViewHeapItem {
    unsigned char opaque[0x188];
    int32_t priority;
};
// `value` may refer to a slot of `heap`; it is intentionally not cached.
void worker_view_heap_push(WorkerViewHeapItem** heap, int32_t hole,
                           int32_t top, WorkerViewHeapItem* const* value);
#endif
