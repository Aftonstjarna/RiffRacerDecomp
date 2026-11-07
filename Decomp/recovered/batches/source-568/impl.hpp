#ifndef RIFF_RECORD68_COPY_HPP
#define RIFF_RECORD68_COPY_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Only the layout and copying behavior are known; names do not imply types
// or ownership. Original VA 0x509ef0, RVA 0x109ef0, size 98 bytes.
struct Record68 {
    uint32_t fields[13];
    struct Tail { uint32_t words[4]; } tail;
    // Constructor-shaped member with an explicit result to expose original EAX.
    // ECX=this, one stack reference, callee removes 4 bytes on i386.
    Record68* RIFF_THISCALL copy_construct(const Record68& source);
};
static_assert(sizeof(Record68) == 68, "original stride");
}
#endif
