#include "impl.hpp"

// VA 0x4f1900. Tag 4 clears the two low mark bits; other
// collectable tags are removed when marked, with tag 7 also testing bit 3.
static bool dead_value(const GCValue& value) {
    uint8_t flags = value.object->flags;
    return (flags & 3) != 0 || (value.tag == 7 && (flags & 8) != 0);
}
void clear_weak_entries(GCTable* table) {
    for (; table; table = table->next) {
        if (table->flags & 0x10) {
            for (uint32_t i = table->array_size; i != 0;) {
                GCValue& value = table->array[--i];
                if (value.tag < 4) continue;
                if (value.tag == 4) value.object->flags &= 0xfc;
                else if (dead_value(value)) value.tag = 0;
            }
        }
        // x86 masks the shift count to five bits.
        uint32_t count = uint32_t(1) << (table->hash_log2 & 31);
        for (uint32_t i = count; i != 0;) {
            GCNode& node = table->nodes[--i];
            if (node.value.tag == 0) continue;
            bool clear = false;
            if (node.key.tag >= 4) {
                if (node.key.tag == 4) node.key.object->flags &= 0xfc;
                else if (node.key.object->flags & 3) clear = true;
            }
            if (!clear && node.value.tag >= 4) {
                if (node.value.tag == 4) node.value.object->flags &= 0xfc;
                else if (dead_value(node.value)) clear = true;
            }
            if (clear) {
                node.value.tag = 0;
                if (node.key.tag >= 4) node.key.tag = 11;
            }
        }
    }
}
void GCTable::clear_weak_entries() { ::clear_weak_entries(this); }
