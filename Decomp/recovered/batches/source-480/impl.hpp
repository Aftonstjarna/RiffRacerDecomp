#ifndef RIFF_TREE_ROTATE_RIGHT_HPP
#define RIFF_TREE_ROTATE_RIGHT_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Recovered link prefix only. Value storage following this prefix is unknown.
struct TreeNode {
    TreeNode* left;        // original +0
    TreeNode* parent;      // original +4
    TreeNode* right;       // original +8
    uint8_t color;         // original +12, untouched by rotation
    uint8_t is_nil;        // original +13, any nonzero value means sentinel
};
struct Tree {
    TreeNode* head;        // head->parent is the root
    void RIFF_THISCALL rotate_right(TreeNode* pivot);
};
}
#endif
