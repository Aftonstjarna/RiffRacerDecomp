#ifndef WORKER_QUEUE_DISPATCH_HPP
#define WORKER_QUEUE_DISPATCH_HPP
#include <stdint.h>

struct QueueRecord { uint32_t first; uint32_t second; char* text; };
struct RecordVector { QueueRecord* begin; QueueRecord* end; QueueRecord* capacity_end; };
struct TextBuffer { char* data; uint32_t used; uint32_t unknown; };

// The original append helper owns vector capacity management.
void append_queue_record(RecordVector* vector, const QueueRecord* record);

struct WorkerQueueOwner {
    unsigned char prefix[0xd1];
    unsigned char disabled;
    void dispatch(uint32_t first, const char* text, uint32_t second, uint32_t vector_index);
};
#endif
