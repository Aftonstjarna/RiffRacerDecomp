#include "impl.hpp"
namespace riff {
// Game.exe VA 0x423180, RVA 0x23180, 84 bytes. Callers such as
// 0x422fc8 and 0x423023 pass the tree in ECX and the pivot on the stack,
// performing color changes themselves. This helper does not rebalance colors.
// Requires readable/writable linked nodes, including a non-null middle child
// (a sentinel is allowed). No null, ordering, or structural checks exist.
void RIFF_THISCALL Tree::rotate_left(TreeNode* pivot) {
    TreeNode* promoted = pivot->right;
    pivot->right = promoted->left;
    if (!promoted->left->is_nil)
        promoted->left->parent = pivot;
    promoted->parent = pivot->parent;
    if (pivot == head->parent)
        head->parent = promoted;
    else if (pivot == pivot->parent->left)
        pivot->parent->left = promoted;
    else
        pivot->parent->right = promoted;
    promoted->left = pivot;
    pivot->parent = promoted;
}
}
