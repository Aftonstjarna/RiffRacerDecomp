#ifndef ARCHIVE_COMPONENT_LOOKUP_HPP
#define ARCHIVE_COMPONENT_LOOKUP_HPP
#include <stdint.h>

struct ArchiveEntry {
    uint16_t name_offset_low;
    uint16_t next;
    uint16_t first_child;
    uint16_t flags_and_index;
};

// Only the fields used by this routine are identified.
struct ArchiveLookup {
    ArchiveEntry* entries;                 // +0x00
    uint32_t unknown_04[5];               // +0x04
    const char* names;                    // +0x18
    ArchiveEntry* lookup(const char* component, const ArchiveEntry* parent);
};
#endif
