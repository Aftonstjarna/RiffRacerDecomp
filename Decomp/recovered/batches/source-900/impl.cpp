#include "impl.hpp"
namespace riff {
// Game.exe VA 0x4f0d10, 99 bytes. Custom ABI: ECX=state, EDX=table,
// [ESP+4]=interned string, caller pops argument, EAX=value slot.
// Callers e.g. 0x4f6443, 0x4f6e06 and 0x557135 inspect slot->tag for nil.
// The portable member uses an explicit service boundary; standard MSVC
// fastcall would incorrectly pop the original's stack argument.
Value* State::ensureStringSlot(Table* table,String* string,const Services& vm) {
 const uint32_t mask=(uint32_t(1) << (table->hashLog2 & 31))-1;
 Node* node=table->nodes+(string->hash & mask);
 // At least the main node is inspected, even with hashLog2 == 0.
 do {
  if(node->key.tag==4 && node->key.payload.string==string) {
   Value* slot=&node->value;
   // Preserve the actual absolute sentinel comparison in the original.
   if(slot!=nilSentinel()) return slot;
   break;
  }
  node=node->next;
 } while(node);
 Value key;
 key.payload.string=string;
 key.tag=4;
 // No cache invalidation here, unlike the general value-slot setter.
 return vm.newKey(this,table,&key);
}
}
