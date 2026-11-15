#ifndef RIFF_RAY_FILTER_HPP
#define RIFF_RAY_FILTER_HPP
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
// Only observed prefixes are represented. Pointer slots remain 32-bit on Linux
// too; these are original object layouts, not reconstructed owning classes.
struct BroadphaseFilter {
    uint32_t opaque04;
    uint16_t group; // +4
    uint16_t mask;  // +6
};
struct RayCallbackFilter {
    uint32_t virtualTable;
    unsigned char opaque04[8];
    uint16_t group; // +12
    uint16_t mask;  // +14
    bool RIFF_THISCALL accepts(const BroadphaseFilter* proxy) const;
};
static_assert(offsetof(RayCallbackFilter, group) == 12, "original layout");
static_assert(offsetof(RayCallbackFilter, mask) == 14, "original layout");
static_assert(offsetof(BroadphaseFilter, group) == 4, "original layout");
static_assert(offsetof(BroadphaseFilter, mask) == 6, "original layout");
}
#endif
