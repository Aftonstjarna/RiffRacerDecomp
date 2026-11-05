#ifndef RIFF_GRAPHICS_RELEASE_ALL_HPP
#define RIFF_GRAPHICS_RELEASE_ALL_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#define RIFF_NORETURN __declspec(noreturn)
#else
#define RIFF_THISCALL __attribute__((thiscall))
#define RIFF_NORETURN __attribute__((noreturn))
#endif
namespace riff {
struct GraphicsEntry {
    uint32_t ownership;
    uint32_t unknown;
    void* resource;
    // Accepted dependency at 0x49ca20; definition belongs to that recovery.
    bool RIFF_THISCALL release(bool force);
};
struct GraphicsEntries {
    GraphicsEntry* begin;
    GraphicsEntry* end;
    GraphicsEntry* capacity;
    // VA 0x4b2400, 118 bytes. Stack argument is callee-popped but unused.
    void RIFF_THISCALL releaseAll(uint32_t unused);
};
// Port binding for the original nonreturning std::_Xout_of_range import.
RIFF_NORETURN void graphicsEntryRangeError();
}
#endif
