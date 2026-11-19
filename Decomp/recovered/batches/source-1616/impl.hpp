#ifndef ARCHIVE_INDEX_HPP
#define ARCHIVE_INDEX_HPP
#include <stdint.h>
struct ArchiveEntry {
    uint16_t name_offset_low, next, first_child, flags_and_index;
};
struct ArchiveIndex {
    ArchiveEntry* entries;             // 00
    uint32_t unknown04[2];             // 04
    unsigned char* records;            // 0c, 28 bytes each
    uint32_t unknown10[2];             // 10
    const char* names;                 // 18
    uint32_t unknown1c[2];             // 1c
    ArchiveEntry root;                 // 24
    // External component helper at 0x5991e0; supplied by the caller/port.
    ArchiveEntry* component(const char*, const ArchiveEntry*);
    void* lookup(const char* path);
};
#endif
