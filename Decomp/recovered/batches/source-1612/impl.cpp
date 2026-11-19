#include "impl.hpp"

// 0x560230, thiscall: range length is recalculated after each failed lookup.
// A valid original range is a contiguous array of 20-byte mount records.
void* MountedArchives::search(const char* path, uint32_t* mount_index) {
    uint32_t i = 0;
    int32_t bytes = static_cast<int32_t>(static_cast<uint32_t>(reinterpret_cast<uintptr_t>(end)) - static_cast<uint32_t>(reinterpret_cast<uintptr_t>(begin)));
    if (bytes / 20 != 0) {
        do {
            void* result = begin[i].index->lookup(path);
            if (result) {
                *mount_index = i;
                return result;
            }
            ++i;
            bytes = static_cast<int32_t>(static_cast<uint32_t>(reinterpret_cast<uintptr_t>(end)) - static_cast<uint32_t>(reinterpret_cast<uintptr_t>(begin)));
        } while (i < static_cast<uint32_t>(bytes / 20));
    }
    *mount_index = 0;
    return 0;
}
