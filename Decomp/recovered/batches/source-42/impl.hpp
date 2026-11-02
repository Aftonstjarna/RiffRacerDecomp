#pragma once
#include <stddef.h>
#include <stdint.h>

namespace riff {
struct Resource;
// The original pushes the interface pointer and the callee removes it.
using Release = uint32_t (__attribute__((stdcall)) *)(Resource*);
struct ResourceVtable { Release slot0; Release slot1; Release release; };
struct Resource { ResourceVtable* vtable; };
// Only this slice of the enclosing object is understood by this routine.
struct RequestOwner {
    unsigned char unknown000[0x43c];
    Resource* resource43c;
    Resource* resource440;
    Resource* resource444;
    Resource* resource448;
};
static_assert(offsetof(RequestOwner, resource43c) == 0x43c, "32-bit layout required");
static_assert(offsetof(RequestOwner, resource448) == 0x448, "32-bit layout required");
bool __attribute__((thiscall)) request_cleanup(RequestOwner* owner);
}
extern "C" bool __attribute__((thiscall)) original_request_cleanup(riff::RequestOwner*);
