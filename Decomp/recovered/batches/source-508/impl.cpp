#include "impl.hpp"
namespace riff {
bool RIFF_THISCALL NarrowTreeKeyLess::operator()(const NarrowString& left,
                                                const NarrowString& right) const {
    // Original calls left.compare(0, left.length, right.data(), right.length)
    // at 0x422be0, then tests its sign. Position zero cannot throw for a valid
    // string. This loop expresses that bounded unsigned-byte comparison.
    const unsigned char* a = left.capacity < 16 ? left.storage.small : left.storage.heap;
    const unsigned char* b = right.capacity < 16 ? right.storage.small : right.storage.heap;
    const uint32_t count = left.length < right.length ? left.length : right.length;
    for (uint32_t i = 0; i < count; ++i) {
        if (a[i] != b[i]) return a[i] < b[i];
    }
    return left.length < right.length;
}
}
// Evidence: callers at 0x42339c/0x4233e0/0x423402/0x42346b/0x423493
// pass keys at node+0x10 and test AL. ECX holds an unused comparator this;
// ret 8 removes two reference arguments. EAX upper bits are not a result.
// No writes, allocation, locale processing, or NUL termination checks occur.
