#ifndef WORKER_STRING_COMPOSE_HPP
#define WORKER_STRING_COMPOSE_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
struct NarrowString {
    union Storage { char local[16]; char* heap; } storage;
    uint32_t length, capacity;
    // External game string methods; allocation and destruction belong to them.
    NarrowString* RIFF_THISCALL append_substring(const NarrowString*, uint32_t, uint32_t);
    NarrowString* RIFF_THISCALL move_construct(NarrowString*);
};
// cdecl, three explicit stack arguments; output denotes uninitialized storage.
NarrowString* worker_string_compose(NarrowString* output, NarrowString* left, const NarrowString* right);
#endif
