#ifndef RIFF_TREE_ITERATOR_HPP
#define RIFF_TREE_ITERATOR_HPP
#include <stdint.h>

namespace riff {
// Original 32-bit node prefix: left +0, parent +4, right +8,
// color +12, sentinel +13. Payload starts at +16 in observed callers.
// Color and payload types are outside this routine's recovered scope.
struct TreeNode {
    TreeNode* left;
    TreeNode* parent;
    TreeNode* right;
    uint8_t color;
    uint8_t sentinel;
    uint8_t reserved[2];
};
struct TreeIterator {
    TreeNode* node;
    TreeIterator* decrement();
};
}
#endif
