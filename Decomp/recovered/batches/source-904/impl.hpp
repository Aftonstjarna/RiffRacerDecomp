#ifndef RIFF_PROTOTYPE_HPP
#define RIFF_PROTOTYPE_HPP
#include <stdint.h>
namespace riff {
struct Prototype {
    uint8_t header[8];
    void* constants;                 // +08: 8-byte tagged values
    void* code;                      // +0c: 4-byte instructions
    void* prototypes;                // +10: 4-byte child pointers
    void* line_info;                 // +14: 4-byte entries
    void* local_variables;           // +18: 12-byte records
    void* upvalue_names;             // +1c: 4-byte string pointers
    void* source;                    // +20: not separately released here
    uint32_t upvalue_count, constant_count, code_count;
    uint32_t line_count, prototype_count, local_count;
    uint8_t tail[16];                // +3c..4b, untouched
};
typedef void* (*Allocator)(void*, void*, uint32_t, uint32_t);
struct Global {
    uint8_t unknown00[12];
    Allocator allocator;
    void* allocator_user;
    uint8_t unknown14[48];
    uint32_t allocated_bytes;        // +44, unsigned modulo arithmetic
};
struct State {
    uint8_t unknown00[16];
    Global* global;
    void dispose_prototype(Prototype* prototype);
};
}
#endif
