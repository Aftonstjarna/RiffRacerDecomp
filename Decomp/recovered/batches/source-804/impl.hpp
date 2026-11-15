#ifndef RIFF_SCRIPT_TABLE_HPP
#define RIFF_SCRIPT_TABLE_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct Table {
    uint8_t unknown00[7];
    uint8_t hash_log2;                 // +7
    uint8_t unknown08[4];
    void* array;                       // +0x0c, 8-byte values
    void* hash;                        // +0x10, 20-byte nodes
    uint8_t unknown14[8];
    uint32_t array_count;              // +0x1c
};
typedef void* (*Allocator)(void*, void*, uint32_t, uint32_t);
struct Global {
    uint8_t unknown00[12];
    Allocator allocator;
    void* allocator_user;
    uint8_t unknown14[48];
    uint32_t allocated_bytes;          // +0x44
};
struct State {
    uint8_t unknown00[16];
    Global* global;
    void destroy_table(Table* table);
};
// The original shared empty-node address is an identity token, never dereferenced.
inline void* empty_hash() { return reinterpret_cast<void*>(uintptr_t(0x99a424)); }
static_assert(sizeof(Table)==32,"original 32-bit table layout");
static_assert(offsetof(Global,allocated_bytes)==68,"original accounting layout");
}
#endif
