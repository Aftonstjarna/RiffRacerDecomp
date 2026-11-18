#ifndef WORKER_RANGE_REPLACE_HPP
#define WORKER_RANGE_REPLACE_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
struct NarrowString {
    union { char local[16]; char* heap; } storage;
    uint32_t length, capacity;
    // Existing string operations, supplied by the wider runtime.
    NarrowString* RIFF_THISCALL erase(uint32_t offset, uint32_t count);
    NarrowString* RIFF_THISCALL replace(uint32_t offset, uint32_t count, const char* source, uint32_t source_count);
    NarrowString* RIFF_THISCALL replace_range(const char* first, const char* last, const char* source_first, const char* source_last);
};
#endif
