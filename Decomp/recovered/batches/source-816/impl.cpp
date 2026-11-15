#include "impl.hpp"
namespace riff {
// Game.exe 0x4f0c50..0x4f0cb0 (97 bytes). Original ABI is custom:
// ECX=state, EDX=table, [ESP+4]=key, caller pops key; EAX returns slot.
// The genuine member below exposes portable dependency boundaries, rather
// than pretending that this is standard fastcall (which would pop the key).
// Caller 0x4f0a3d retries here after rehash and removes both pending keys.
Value* State::ensureValueSlot(Table* table,const Value* key,const Services& vm) {
    Value* slot=vm.getValue(table,key);
    // Invalidate cached metamethod absence flags even for an existing slot.
    table->header[6]=0;
    if(slot!=nilSentinel()) return slot;
    if(key->tag==0) {
        vm.runtimeError(this,"table index is nil"); // original string 0x9fd750
    } else if(key->tag==3) {
        // UCOMISS x,x rejects unordered only: zeros and infinities are valid.
        const float number=key->payload.number;
        if(number!=number) vm.runtimeError(this,"table index is NaN"); // 0x9fd714
    }
    // Original continues here if the error helper returns; normally VM error
    // dispatch does not return. Preserve that ordering and possible return.
    return vm.newKey(this,table,key);
}
}
