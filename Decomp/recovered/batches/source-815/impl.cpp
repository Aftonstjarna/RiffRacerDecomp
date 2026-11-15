#include "impl.hpp"
namespace riff {
// Game.exe 0x4f0660..0x4f0800. ECX=state, EDX=table, two caller-popped
// stack words. Callers 0x4f08dd (rehash) and 0x4f43b1 confirm this order.
// The portable member deliberately leaves the VM dependencies explicit.
void State::resize(Table* t,int32_t requested,int32_t hashRequest,const Services& vm) {
 const int32_t oldSize=t->arraySize;
 const uint8_t oldLog=t->hashLog2;
 Node* const oldNodes=t->nodes;
 if(requested>oldSize) vm.resizeArray(this,t,requested);
 vm.initializeHash(this,t,hashRequest);
 if(requested<oldSize) {
  t->arraySize=requested;
  for(int32_t i=requested;i<oldSize;++i) {
   // Capture the source before insertion: the helper may change t->array.
   Value* const source=t->array;
   if(source[i].tag!=0) {
    Value* dest=vm.ensureInteger(this,t,int32_t(uint32_t(i)+1u));
    dest->payload.bits=source[i].payload.bits;
    dest->tag=source[i].tag;
   }
  }
  void* replacement=0;
  if(uint32_t(requested)+1u<=0x1fffffffu)
   replacement=vm.reallocate(this,t->array,uint32_t(oldSize)*8u,uint32_t(requested)*8u);
  else vm.error(this,ArrayTooLarge);
  t->array=static_cast<Value*>(replacement);
 }
 const uint32_t oldCount=uint32_t(1)<<(oldLog&31);
 // The original tests the signed descending index, including x86 shift masking.
 for(int32_t i=int32_t(oldCount-1u);i>=0;--i) {
  Node* n=oldNodes+i;
  if(n->value.tag!=0) {
   Value* dest=vm.lookup(t,&n->key);
   t->header[6]=0;
   if(dest==nilValue()) {
    if(n->key.tag==0) vm.error(this,NilKey);
    else if(n->key.tag==3 && n->key.payload.number!=n->key.payload.number)
     vm.error(this,NaNKey);
    dest=vm.newKey(this,t,&n->key);
   }
   dest->payload.bits=n->value.payload.bits;
   dest->tag=n->value.tag;
  }
 }
 if(oldNodes!=emptyHash()) vm.reallocate(this,oldNodes,oldCount*20u,0);
}
}
