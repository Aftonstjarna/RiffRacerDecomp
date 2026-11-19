#ifndef MOUNTED_ARCHIVE_SEARCH_HPP
#define MOUNTED_ARCHIVE_SEARCH_HPP
#include <stdint.h>

// External archive index implementation, outside this recovery's scope.
struct ArchiveIndex {
    void* lookup(const char* path);
};
struct MountRecord {
    uint32_t unknown0, unknown4;
    ArchiveIndex* index;
    uint32_t unknown12, unknown16;
};
struct MountedArchives {
    uint8_t unknown[0x48];
    MountRecord* begin;
    MountRecord* end;
    void* search(const char* path, uint32_t* mount_index);
};
#endif
