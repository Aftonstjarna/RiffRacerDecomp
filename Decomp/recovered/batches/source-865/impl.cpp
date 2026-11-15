#include "impl.hpp"
#include <stddef.h>
namespace riff {
#if UINTPTR_MAX == 0xffffffffu
static_assert(sizeof(Node)==20, "original node stride");
static_assert(offsetof(Metatable,nodes)==0x10, "node pointer offset");
static_assert(offsetof(GlobalState,metamethodNames)==0xa0, "event names offset");
static_assert(offsetof(ScriptState,global)==0x10, "global offset");
#endif
const Value* originalNilAddress() {
    // Shared immutable TValue at original VA 0x99a41c. A native engine port
    // should rebind this to its shared nil object, preserving pointer identity.
    return reinterpret_cast<const Value*>(static_cast<uintptr_t>(0x99a41c));
}
const Value* ScriptState::lookupMetamethod(const Value* value, uint32_t event) const {
    Metatable* table;
    if (value->tag == 5 || value->tag == 7) {
        const ScriptObject* object = reinterpret_cast<const ScriptObject*>(
            static_cast<uintptr_t>(value->payload));
        table = object->metatable;
    } else {
        table = global->typeMetatables[value->tag];
    }
    if (!table) return originalNilAddress();
    InternedName* name = global->metamethodNames[event];
    // x86 SHL masks CL to five bits, including for counts >=32.
    const uint32_t mask = (uint32_t(1) << (table->logNodeCount & 31)) - 1;
    const Node* node = table->nodes + (name->hash & mask);
    do {
        if (node->keyTag == 4 && node->key == name) return &node->value;
        node = node->next;
    } while (node);
    return originalNilAddress();
}
}
