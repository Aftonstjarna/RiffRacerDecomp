#ifndef RIFF_NARROW_RANGE_HPP
#define RIFF_NARROW_RANGE_HPP
namespace riff {
// MSVC 32-bit narrow-string representation, not a native Linux std::string.
struct NarrowString32 {
    unsigned char storage[16]; // inline bytes, or heap pointer in first four bytes
    unsigned size;
    unsigned capacity;
};
static_assert(sizeof(unsigned) == 4 && sizeof(NarrowString32) == 24, "32-bit layout");
#if defined(_MSC_VER)
using Delete = void (__cdecl *)(void*);
#else
using Delete = void (__attribute__((cdecl)) *)(void*);
#endif
// The injected dependency is the game's cdecl operator-delete import.
// Valid range endpoints must differ by a nonnegative multiple of 24 bytes.
void destroy_narrow_range(NarrowString32* first, NarrowString32* last, Delete release);
}
#endif
