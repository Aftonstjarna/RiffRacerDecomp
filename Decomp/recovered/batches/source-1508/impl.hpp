#ifndef WORKER_EMPTY_STRING_HPP
#define WORKER_EMPTY_STRING_HPP
#include <stdint.h>
struct WorkerString {
    unsigned char inline_storage[16];
    uint32_t length;
    uint32_t capacity;
};
// VA 0x4571b0: cdecl, destination is the first stack argument.
WorkerString* worker_empty_string_construct(WorkerString* destination);
#endif
