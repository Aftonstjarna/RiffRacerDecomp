#ifndef RIFF_NARROW_DESTROY_HPP
#define RIFF_NARROW_DESTROY_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
namespace riff {
typedef void (RIFF_CDECL *ScalarDelete)(void*);
// Platform binding for the scalar operator-delete import at original 0x92d4b0.
// The embedding port supplies this pointer; it must accept null as the CRT does.
extern ScalarDelete scalar_delete;
struct NarrowString {
    union Storage { char inline_bytes[16]; void* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    void destroy();
};
static_assert(sizeof(NarrowString) == 24, "requires original 32-bit layout");
static_assert(offsetof(NarrowString, length) == 16, "length offset");
static_assert(offsetof(NarrowString, capacity) == 20, "capacity offset");
}
#endif
