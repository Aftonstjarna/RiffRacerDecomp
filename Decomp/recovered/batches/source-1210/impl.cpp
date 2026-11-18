#include "impl.hpp"
// VA 0x5c20e0. Caller 0x5c1de6 appends a zero byte before
// passing the vector's first pointer to another routine.
void WORKER_THISCALL WorkerByteVector::append(const unsigned char* source) {
    const uintptr_t address = reinterpret_cast<uintptr_t>(source);
    const uintptr_t start = reinterpret_cast<uintptr_t>(first);
    const bool internal = address >= start && address < reinterpret_cast<uintptr_t>(last);
    const uintptr_t offset = address - start;
    if (last == capacity_end) grow(1);
    if (last) {
        const unsigned char* input = internal
            ? reinterpret_cast<const unsigned char*>(reinterpret_cast<uintptr_t>(first) + offset)
            : source;
        *last = *input;
    }
    // The machine increments even a null end; avoid null pointer arithmetic.
    last = reinterpret_cast<unsigned char*>(reinterpret_cast<uintptr_t>(last) + 1);
}
