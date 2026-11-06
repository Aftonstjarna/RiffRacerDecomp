#ifndef RIFF_NARROW_TREE_KEY_LESS_HPP
#define RIFF_NARROW_TREE_KEY_LESS_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
// Original 32-bit narrow-string layout. Capacity selects storage, not length.
struct NarrowString {
    union Storage { unsigned char small[16]; const unsigned char* heap; } storage;
    uint32_t length;
    uint32_t capacity;
};
// VA 0x422c50, 43 bytes. The original never reads its comparator object.
struct NarrowTreeKeyLess {
    bool RIFF_THISCALL operator()(const NarrowString& left,
                                 const NarrowString& right) const;
};
#if defined(_MSC_VER) || defined(__i386__)
static_assert(sizeof(NarrowString) == 24, "original i386 string layout");
#endif
}
#endif
