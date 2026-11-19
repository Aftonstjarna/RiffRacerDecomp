#include "impl.hpp"

// 0x598d50, thiscall. The original has an unchecked 512-byte local copy.
void* ArchiveIndex::lookup(const char* path) {
    char copy[512];
    unsigned length = 0;
    while (path[length]) ++length;
    for (unsigned i = 0; i <= length; ++i) copy[i] = path[i];
    unsigned separators = 0;
    for (unsigned i = 0; i < length; ++i) {
        if (copy[i] == '\\') { copy[i] = 0; ++separators; }
    }
    const char* part = copy;
    const ArchiveEntry* parent = &root;
    for (unsigned i = 0; i <= separators; ++i) {
        parent = component(part, parent);
        if (!parent) return 0;
        while (*part) ++part;
        ++part;
    }
    return records + (parent->flags_and_index & 0x3fffU) * 28U;
}
