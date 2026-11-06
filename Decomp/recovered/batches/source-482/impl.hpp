#ifndef RIFF_TREE_ROTATE_LEFT_HPP
#define RIFF_TREE_ROTATE_LEFT_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Recovered node prefix. Payload type/extent is unknown and not accessed.
// On original i386: left +0, parent +4, right +8, color +12, nil +13.
struct TreeNode {
    TreeNode* left;
    TreeNode* parent;
    TreeNode* right;
    uint8_t color;
    uint8_t is_nil;
};
// Only the first pointer of the original tree object is established here.
struct Tree {
    TreeNode* head;
    void RIFF_THISCALL rotate_left(TreeNode* pivot);
};
}
#endif
