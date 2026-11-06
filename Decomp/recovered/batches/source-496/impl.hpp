#ifndef RIFF_TREE_ITERATOR_HPP
#define RIFF_TREE_ITERATOR_HPP
#include <stdint.h>
// Original node prefix: pointers at +0,+4,+8; marker at +13 (i386).
// +12 is conventionally the tree color; this routine never reads it.
struct TreeNode {
    TreeNode* left;
    TreeNode* parent;
    TreeNode* right;
    uint8_t color;
    uint8_t is_nil;
    uint8_t opaque[2];
};
struct TreeIterator {
    TreeNode* node;
#ifdef _MSC_VER
    TreeIterator& __thiscall increment();
#else
    TreeIterator& __attribute__((thiscall)) increment();
#endif
};
#endif
