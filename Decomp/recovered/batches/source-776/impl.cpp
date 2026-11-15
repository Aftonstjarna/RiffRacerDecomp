#include "impl.hpp"
namespace riff {
// Game.exe VA 0x4f0b70, 56 bytes. Caller at 0x4f0bc6 extracts a
// type-4 key and tail-calls with table in ECX, string in EDX (fastcall).
// No allocation, mutation, content comparison, or sentinel dereference.
ScriptNode* RIFF_FASTCALL ScriptTable::getString(const ScriptString* key) const {
    const uint32_t mask = (uint32_t(1) << (logNodeCount & 31u)) - 1u;
    ScriptNode* node = nodes + (key->hash & mask);
    do {
        if (node->keyType == 4 && node->key == key)
            return node;
        node = node->next;
    } while (node);
    return reinterpret_cast<ScriptNode*>(uintptr_t(0x99a41c));
}
}
