#ifndef RIFF_NARROW_TREE_HPP
#define RIFF_NARROW_TREE_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Original 32-bit MSVC narrow string: capacity >=16 selects the pointer.
struct NarrowString {
    union Storage { unsigned char local[16]; const unsigned char* heap; } storage;
    uint32_t length;
    uint32_t capacity;
    const unsigned char* data() const {
        return capacity < 16 ? storage.local : storage.heap;
    }
};
struct NarrowNode {
    NarrowNode* left;
    NarrowNode* parent;
    NarrowNode* right;
    uint8_t color;             // Unused by this search.
    uint8_t sentinel;          // Any nonzero value terminates traversal.
    uint8_t unused[2];
    NarrowString key;
    // Mapped value, if any, follows the key; its type is outside this routine.
};
struct NarrowTree {
    NarrowNode* head;
    NarrowNode* RIFF_THISCALL lower_bound(const NarrowString* query) const;
};
}
#endif
