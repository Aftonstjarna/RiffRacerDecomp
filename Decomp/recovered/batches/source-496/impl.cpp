#include "impl.hpp"
// Game.exe 0x422e20..0x422e6f. No allocation, imports or node writes.
// Callers at 0x42347d and 0x42a81e pass a one-pointer local in ECX.
// Links must be valid, sentinel-terminated tree links; no null checks exist.
TreeIterator& TreeIterator::increment() {
    if (!node->is_nil) {
        if (!node->right->is_nil) {
            TreeNode* next = node->right;
            while (!next->left->is_nil)
                next = next->left;
            node = next;
        } else {
            TreeNode* next = node->parent;
            while (!next->is_nil && node == next->right) {
                // Preserve the original's intermediate iterator stores.
                node = next;
                next = next->parent;
            }
            node = next;
        }
    }
    return *this;
}
