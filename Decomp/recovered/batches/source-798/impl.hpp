#ifndef RIFF_SCRIPT_ARRAY_HPP
#define RIFF_SCRIPT_ARRAY_HPP
#include <stdint.h>
namespace riff {
struct Value { uint32_t payload, tag; };
struct Table {
    uint8_t header[12];
    Value* array;                 // original x86 +0x0c
    uint32_t other[3];
    int32_t array_size;            // original x86 +0x1c
};
// External script-runtime services, deliberately outside this recovery's scope.
struct ArrayServices {
    void* (*reallocate)(void* state, void* memory, uint32_t old_bytes, uint32_t new_bytes);
    void* (*allocation_too_large)(void* state);
};
void resize_array(void* state, Table* table, int32_t count, const ArrayServices& services);
}
#endif
