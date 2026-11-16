#ifndef RECORD48_IMPL_HPP
#define RECORD48_IMPL_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RECORD48_FASTCALL __fastcall
#elif defined(__i386__)
#define RECORD48_FASTCALL __attribute__((fastcall))
#else
#define RECORD48_FASTCALL
#endif
// Original field meanings are unresolved. Names describe only observed writes.
struct Record48 {
    uint32_t zeroedWords[9]; // +0 .. +32
    uint32_t preservedWord;  // +36
    uint32_t zeroedWord40;   // +40
    uint8_t zeroedByte44;    // +44
    uint8_t preservedTail[3];
};
static_assert(sizeof(Record48) == 48, "original stride");
static_assert(offsetof(Record48, zeroedWord40) == 40, "original layout");
static_assert(offsetof(Record48, zeroedByte44) == 44, "original layout");
// Range helper, not an instance method: ECX=first, EDX=count, no stack args.
// Each non-null element address must designate writable Record48 storage.
extern "C" void RECORD48_FASTCALL record48_default_construct_range(Record48* first, uint32_t count);
#endif
