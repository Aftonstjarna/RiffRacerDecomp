#ifndef RIFF_RANGE_MOVE_HPP
#define RIFF_RANGE_MOVE_HPP
#include <stdint.h>
// Original x86 layout. The inline buffer also holds the owned heap pointer.
struct NarrowString {
    union Storage { unsigned char local[16]; unsigned char* heap; } storage;
    uint32_t length;
    uint32_t capacity;
};
static_assert(sizeof(NarrowString)==24,"24-byte string stride required");
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL
#endif
// VA 0x426960, cdecl: first, last (exclusive), raw destination. EAX is end.
NarrowString* RIFF_CDECL narrow_range_move_construct(
    NarrowString* first, NarrowString* last, NarrowString* destination);
#endif
