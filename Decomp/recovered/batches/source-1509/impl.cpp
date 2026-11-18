#include "impl.hpp"

WorkerRefObject** worker_ref_pointer_range_copy(WorkerRefObject* const* first,
    WorkerRefObject* const* last, WorkerRefObject** output)
{
    // Integer address arithmetic also captures the original's null-output
    // single-element case: it skips that element and returns address 4.
    uintptr_t destination = reinterpret_cast<uintptr_t>(output);
    while (first != last) {
        if (destination != 0) {
            WorkerRefObject* object = *first;
            *reinterpret_cast<WorkerRefObject**>(destination) = object;
            if (object != 0) {
                char* base = reinterpret_cast<char*>(object);
                uint32_t* count = reinterpret_cast<uint32_t*>(
                    base + object->metadata->counter_offset + 4);
                ++*count;
            }
        }
        ++first;
        destination += sizeof(WorkerRefObject*);
    }
    return reinterpret_cast<WorkerRefObject**>(destination);
}
