#include "impl.hpp"

void WorkerQueueOwner::dispatch(uint32_t first, const char* text,
                                uint32_t second, uint32_t vector_index) {
    if (disabled) return;
    unsigned char* base = reinterpret_cast<unsigned char*>(this);
    uint32_t buffer_index = *reinterpret_cast<uint32_t*>(base + 0x2cd8);
    TextBuffer* buffer = reinterpret_cast<TextBuffer*>(base + 0x2c9c + buffer_index * 12u);
    uint32_t length = 0;
    while (text[length]) ++length;
    ++length;
    char* destination = buffer->data + buffer->used;
    buffer->used += length;
    for (uint32_t i = 0; i < length; ++i) destination[i] = text[i];
    QueueRecord record = { first, second, destination };
    RecordVector* vector = reinterpret_cast<RecordVector*>(base + 0x78 + vector_index * 12u);
    append_queue_record(vector, &record);
}
