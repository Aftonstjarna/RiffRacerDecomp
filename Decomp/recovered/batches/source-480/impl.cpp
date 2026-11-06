#include "impl.hpp"
namespace riff {
// Game.exe 0x4231e0..0x423238, RVA 0x231e0. ECX=this,
// one stack argument, ret 4. Callers include erase balancing at 0x423042
// and insertion balancing at 0x423781; they perform their own recoloring.
// Preconditions inherited from those callers: valid header, pivot, left
// child and transferred right link. Nil links are sentinel objects, not null.
// No allocation, comparison of keys, recoloring or size update occurs here.
void RIFF_THISCALL Tree::rotate_right(TreeNode* pivot) {
    TreeNode* promoted = pivot->left;
    pivot->left = promoted->right;
    if (promoted->right->is_nil == 0)
        promoted->right->parent = pivot;
    promoted->parent = pivot->parent;
    if (pivot == head->parent)
        head->parent = promoted;
    else if (pivot == pivot->parent->right)
        pivot->parent->right = promoted;
    else
        pivot->parent->left = promoted;
    promoted->right = pivot;
    pivot->parent = promoted;
}
}
