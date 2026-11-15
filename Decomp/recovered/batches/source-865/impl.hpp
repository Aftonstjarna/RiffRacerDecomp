#ifndef RIFF_SCRIPT_METAMETHOD_HPP
#define RIFF_SCRIPT_METAMETHOD_HPP
#include <stdint.h>
namespace riff {
struct Metatable;
// Only fields read by this bounded routine are named; other bytes remain opaque.
struct Value { uint32_t payload; uint32_t tag; };
struct InternedName { uint8_t opaque[8]; uint32_t hash; };
struct Node { Value value; InternedName* key; uint32_t keyTag; Node* next; };
struct Metatable {
    uint8_t opaque0[7]; uint8_t logNodeCount;
    uint8_t opaque8[8]; Node* nodes;
};
struct ScriptObject { uint8_t opaque[8]; Metatable* metatable; };
struct GlobalState {
    uint8_t opaque[0x7c];
    Metatable* typeMetatables[9];
    InternedName* metamethodNames[18];
};
struct ScriptState {
    uint8_t opaque[0x10]; GlobalState* global;
    // Portable member model of VA 0x4f5d00. Original internal ABI is
    // ECX=state, EDX=value, [ESP+4]=event, caller stack cleanup.
    // This ordinary member intentionally does not claim that custom ABI.
    const Value* lookupMetamethod(const Value* value, uint32_t event) const;
};
const Value* originalNilAddress();
}
#endif
