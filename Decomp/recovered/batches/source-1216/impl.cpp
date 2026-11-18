#include "impl.hpp"

// 0x519d50. Arithmetic is explicitly 32-bit, as in the original x86 code.
void WORKER_THISCALL WorkerByteVector::ensure_spare(uint32_t count) {
    uint32_t begin = (uint32_t)(uintptr_t)first;
    uint32_t end = (uint32_t)(uintptr_t)last;
    uint32_t limit = (uint32_t)(uintptr_t)capacity_end;
    if (limit - end >= count) return;

    if (begin - end - 1u < count)
        worker_byte_vector_length_error("vector<T> too long");

    uint32_t required = end - begin + count;
    uint32_t capacity = limit - begin;
    uint32_t half = capacity >> 1;
    uint32_t grown = (0xffffffffu - half < capacity) ? 0u : capacity + half;
    if (grown < required) grown = required;
    reallocate(grown);
}
