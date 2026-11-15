#include "impl.hpp"
namespace riff {
// Game.exe 0x4f0cc0..0x4f0d0d. Original custom ABI: ECX=state,
// EDX=table, [ESP+4]=signed key; caller removes the stack argument.
// The portable member keeps dependency calls explicit instead of encoding that
// nonstandard ABI. Callers at 0x420103/0x420178 subsequently write the value.
Value* State::ensureIntegerSlot(Table* table,int32_t integer,const Services& vm) {
    Value* slot=vm.getInteger(table,integer);
    // Pointer identity is essential: an existing slot tagged nil still exists.
    // Unlike the general setter (0x4f0c50), this never clears header byte +6.
    if(slot!=nilSentinel()) return slot;
    Value key;
    // Original CVTDQ2PS uses signed conversion and current MXCSR rounding.
    // Large integers can alias the same single-precision numeric key.
    key.payload.number=static_cast<float>(integer);
    key.tag=3;
    return vm.newKey(this,table,&key);
}
}
