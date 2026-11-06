#include "impl.hpp"

namespace riff {
// Game.exe 0x4235a0..0x4235fe, no arguments beyond this, returns this.
// Only the iterator pointer is written. Valid linked nodes and sentinel are
// required; null links and cyclic malformed ancestry are not handled.
// Callers at 0x4233f2, 0x4238fb and 0x42a7ac pass stack iterators in ECX.
TreeIterator* TreeIterator::decrement() {
    if (node->sentinel != 0) {
        node = node->right;
    } else if (node->left->sentinel == 0) {
        TreeNode* predecessor = node->left;
        while (predecessor->right->sentinel == 0)
            predecessor = predecessor->right;
        node = predecessor;
    } else {
        TreeNode* ancestor = node->parent;
        while (ancestor->sentinel == 0 && node == ancestor->left) {
            node = ancestor;
            ancestor = ancestor->parent;
        }
        // Retain the original check, including its behavior for unusual links.
        if (node->sentinel == 0)
            node = ancestor;
    }
    return this;
}
}
