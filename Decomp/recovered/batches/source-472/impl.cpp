#include "impl.hpp"
namespace riff {
// Game.exe VA 0x423240, RVA 0x23240, 30 bytes. ECX=this, EAX=result,
// no stack arguments, no writes, no calls. Original callers at 0x422f20,
// 0x429e1f and 0x5a0a7f store the result into a header's rightmost link.
// Only the *next* node's sentinel flag is tested, never this node's flag.
// Valid input requires a readable, terminating right chain with a sentinel;
// null pointers and cycles are not handled by the original.
TreeNode* RIFF_THISCALL TreeNode::rightmost() {
    TreeNode* current = this;
    while (current->right->is_nil == 0)
        current = current->right;
    return current;
}
}
