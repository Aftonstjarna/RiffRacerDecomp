#ifndef RIFF_NARROW_END_POINTER_HPP
#define RIFF_NARROW_END_POINTER_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Recovered 32-bit narrow-string layout; names describe observed fields.
struct NarrowString {
    union Storage {
        char inline_bytes[16];
        char* heap;
    } storage;
    uint32_t length;
    uint32_t capacity;
    char** RIFF_THISCALL end_pointer(char** result);
};
static_assert(offsetof(NarrowString, length) == 16, "length offset");
static_assert(offsetof(NarrowString, capacity) == 20, "capacity offset");
static_assert(sizeof(NarrowString) == 24, "string layout");
}
#endif
