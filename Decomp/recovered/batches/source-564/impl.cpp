#include "impl.hpp"
namespace riff {
// Game.exe 0x422d40..0x422e19. ECX=this, one callee-popped pointer
// argument, EAX=node. No allocations, imports, writes, or FS registration.
// Callers at 0x422aa1 and 0x422b3c compare the result to head before
// checking equality: this is lower_bound, not an exact lookup.
NarrowNode* RIFF_THISCALL NarrowTree::lower_bound(const NarrowString* query) const {
    NarrowNode* candidate = head;
    NarrowNode* node = head->parent;
    while (!node->sentinel) {
        const NarrowString& key = node->key;
        const unsigned char* a = key.data();
        const unsigned char* b = query->data();
        const uint32_t count = key.length < query->length ? key.length : query->length;
        uint32_t i = 0;
        // Original compares four-byte chunks for equality, then locates the
        // first differing unsigned byte. Bytewise comparison has the same
        // result for valid readable strings, without alignment/aliasing UB.
        while (i < count && a[i] == b[i]) ++i;
        const bool less = i < count ? a[i] < b[i] : key.length < query->length;
        if (less) {
            node = node->right;
        } else {
            candidate = node;
            node = node->left;
        }
    }
    // Empty trees never dereference query (which may consequently be null).
    return candidate;
}
}
