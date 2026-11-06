#ifndef RIFF_TREE_RIGHTMOST_HPP
#define RIFF_TREE_RIGHTMOST_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Recovered node prefix only; the value/payload and owning tree type are unknown.
struct TreeNode {
    TreeNode* left;
    TreeNode* parent;
    TreeNode* right;
    uint8_t color; // Adjacent tree code uses +12; irrelevant to this routine.
    uint8_t is_nil;
    uint8_t opaque[2];
    TreeNode* RIFF_THISCALL rightmost();
};
#if UINTPTR_MAX == 0xffffffffu
static_assert(offsetof(TreeNode, right) == 8, "original right offset");
static_assert(offsetof(TreeNode, is_nil) == 13, "original sentinel offset");
static_assert(sizeof(TreeNode) == 16, "node prefix size");
#endif
}
#endif
