#ifndef RIFF_RECORD48_HPP
#define RIFF_RECORD48_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Only the counter at +4 is established by this routine. The first word's
// meaning, resource type and destruction protocol remain unresolved.
struct RetainedHeader { uint32_t unknown; uint32_t references; };
struct Record48 {
    RetainedHeader* retained[4];
    uint32_t words[8];
    // VA 0x004b4310, 110 bytes. ECX=this, stack source, callee pops 4,
    // EAX=this. Caller 0x004b3eb0 constructs a range with a 48-byte stride.
    // This behaves like a copy constructor, not an owning assignment:
    // existing destination references are overwritten without release.
    Record48* RIFF_THISCALL copyRetain(const Record48* source);
};
}
#endif
