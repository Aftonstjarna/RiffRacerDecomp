#ifndef WORKER_REF_POINTER_RANGE_COPY_HPP
#define WORKER_REF_POINTER_RANGE_COPY_HPP
#include <stdint.h>

// The first word of each referent points to metadata whose second word is
// a signed byte displacement. The counter is at referent + displacement + 4.
struct WorkerRefMetadata { uint32_t unknown; int32_t counter_offset; };
struct WorkerRefObject { const WorkerRefMetadata* metadata; };

// Returns the advanced output address, as the original leaves it in EAX.
WorkerRefObject** worker_ref_pointer_range_copy(WorkerRefObject* const* first,
    WorkerRefObject* const* last, WorkerRefObject** output);
#endif
