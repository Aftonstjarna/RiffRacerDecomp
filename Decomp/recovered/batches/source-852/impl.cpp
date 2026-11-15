#include "impl.hpp"
namespace riff {
Value* ScriptTable::cached_event_lookup(uint32_t event, const ScriptString* name) {
    // x86 masks the shift count to five bits even for unusual exponents.
    const uint32_t mask = (uint32_t(1) << (hash_exponent & 31)) - 1;
    Node* node = nodes + (name->hash & mask);
    while (node) {
        if (node->key_tag == 4 && node->key == name) {
            if (node->value.tag != 0) return &node->value;
            break;
        }
        node = node->next;
    }
    // The original miss selects the shared nil TValue at 0x99a41c (two
    // zero words in Game.exe). Both that nil and an explicit nil value take
    // this path. No nil sentinel pointer escapes this function.
    // SHL AL,CL truncates to eight bits, but masks CL to five, not three.
    absent_events |= static_cast<uint8_t>(uint32_t(1) << (event & 31));
    return 0;
}
}
