#include "impl.hpp"
namespace riff {
// Game.exe 0x4f0900..0x4f0971, original custom ABI: ECX=state,
// EDX=array count, stack=hash count, caller cleans stack, EAX=result.
// Callers include 0x441b7c (empty table), 0x48511c (0 array, 2 hash),
// and VM new-table instruction 0x4f3724 (decoded array/hash capacities).
// A portable state member replaces that nonstandard register convention.
Table* State::construct_table(int32_t array_count, int32_t hash_count, const Services& services) {
    Table* table = static_cast<Table*>(services.reallocate(this,0,0,32));
    // Reload after allocation: the allocator may have changed state.global.
    Global* owner = global;
    table->next = owner->gc_head;
    uint8_t white = owner->current_white;
    owner->gc_head = table;
    table->marked = white & 3;
    table->type = 5;
    table->metatable = 0;
    table->flags = 255;
    table->hash_log2 = 0;
    table->array = 0;
    table->array_count = 0;
    table->hash = empty_hash();
    // +0x14 is established by initialize_hash; +0x18 is never written here.
    services.resize_array(this,table,array_count);
    services.initialize_hash(this,table,hash_count);
    return table;
}
}
