#ifndef RIFF_GRAPHICS_ENTRY_RELEASE_HPP
#define RIFF_GRAPHICS_ENTRY_RELEASE_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
struct ReferenceBase;
// Slot zero has the observed scalar-deleting-destructor calling convention.
// Its return value is ignored. Full class identity and other slots are unknown.
typedef void* (RIFF_THISCALL *DeletingDestructor)(ReferenceBase*, uint32_t);
struct ReferenceVtable { DeletingDestructor destroy; };
struct ReferenceBase { const ReferenceVtable* vtable; uint32_t references; };
struct ResourcePrefix {
    uint32_t unknown;
    const int32_t* virtualBaseOffsets;
};
struct GraphicsEntry {
    uint32_t ownership;
    uint32_t unknown;
    ResourcePrefix* resource;
    bool RIFF_THISCALL release(bool force);
};
}
#endif
