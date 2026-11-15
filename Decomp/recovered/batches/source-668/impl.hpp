#ifndef RIFF_CONVEX_FILTER_HPP
#define RIFF_CONVEX_FILTER_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Only the observed eight-byte prefix is modeled, not the complete game type.
// +0 is an opaque original 32-bit vtable address, never dereferenced here.
struct ConvexCallbackFilter {
    uint32_t opaque_vtable;
    uint16_t group;
    uint16_t mask;
    bool RIFF_THISCALL accepts(const ConvexCallbackFilter* other) const;
};
static_assert(offsetof(ConvexCallbackFilter, group) == 4, "group offset");
static_assert(offsetof(ConvexCallbackFilter, mask) == 6, "mask offset");
static_assert(sizeof(ConvexCallbackFilter) == 8, "observed prefix size");
#endif
