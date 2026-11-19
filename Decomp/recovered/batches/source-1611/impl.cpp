#include "impl.hpp"

// Original: 0x5991e0, thiscall, callee pops two arguments.
ArchiveEntry* ArchiveLookup::lookup(const char* component, const ArchiveEntry* parent) {
    uint16_t index = parent->first_child;
    while (index != 0xffff) {
        ArchiveEntry* entry = entries + index;
        unsigned offset = entry->name_offset_low |
            (static_cast<unsigned>(entry->flags_and_index & 0xc000) << 2);
        const char* a = names + offset;
        const char* b = component;
        while (*a == *b && *a != '\0') { ++a; ++b; }
        if (*a == *b) return entry;
        index = entry->next;
    }
    return 0;
}
