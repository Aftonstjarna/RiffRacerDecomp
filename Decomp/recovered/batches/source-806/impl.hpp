#ifndef RIFF_TABLE_CONSTRUCT_HPP
#define RIFF_TABLE_CONSTRUCT_HPP
#include <stdint.h>
namespace riff {
struct Table {
    Table* next;
    uint8_t type, marked, flags, hash_log2;
    void* metatable;
    void* array;
    void* hash;
    void* last_free;
    uint32_t untouched18;
    int32_t array_count;
};
struct Global {
    uint8_t prefix[12];
    void* (*allocator)(void*,void*,uint32_t,uint32_t);
    void* allocator_user;
    uint8_t current_white;
    uint8_t unknown15[7];
    Table* gc_head;
    uint8_t unknown20[36];
    uint32_t allocated_bytes;
};
struct Services;
struct State {
    uint8_t prefix[16];
    Global* global;
    Table* construct_table(int32_t array_count, int32_t hash_count, const Services&);
};
// Accepted VM helpers remain dependencies; their allocation/error semantics are
// not reimplemented by this bounded constructor recovery.
struct Services {
    void* (*reallocate)(State*,void*,uint32_t,uint32_t);
    void (*resize_array)(State*,Table*,int32_t);
    void (*initialize_hash)(State*,Table*,int32_t);
};
inline void* empty_hash() { return reinterpret_cast<void*>(uintptr_t(0x99a424)); }
}
#endif
