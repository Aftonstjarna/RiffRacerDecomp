#include "impl.hpp"
namespace riff {
// Game.exe 0x4f0520..0x4f0577. Original custom caller-cleaned ABI:
// ECX=script state, EDX=table, [ESP+4]=count. Not a conventional thiscall.
// Callers 0x4f0690 (table rehash) and 0x4f0956 (table creation).
void resize_array(void* state, Table* table, int32_t count, const ArrayServices& services) {
    void* memory;
    // Unsigned wrapping addition is intentional: -1 passes this guard.
    if (uint32_t(count) + uint32_t(1) > 0x1fffffffu)
        memory = services.allocation_too_large(state);
    else
        memory = services.reallocate(state, table->array,
            uint32_t(table->array_size) * 8u, uint32_t(count) * 8u);
    table->array = static_cast<Value*>(memory);
    // Signed comparisons, including when shrinking. Only the nil tag is set;
    // payloads, existing tags, and other table fields remain untouched.
    for (int32_t i = table->array_size; i < count; ++i)
        table->array[i].tag = 0;
    table->array_size = count;
}
}
