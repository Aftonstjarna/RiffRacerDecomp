#include "impl.hpp"
namespace riff {
// Game.exe 0x4f09e0..0x4f0adc. Custom register ABI: ECX=state,
// EDX=table, stack key, caller cleanup. This member is the portable interface;
// the extra Services argument exposes dependencies instead of fixing addresses.
// Callers 0x4f0ca4/0x4f0cff validate or construct keys before arriving here.
Value* State::newKey(Table* t,const Value* key,const Services& vm) {
 Node* bucket=vm.mainBucket(t,key);
 if(bucket->value.tag!=0 || uintptr_t(bucket)==0x99a424u) {
  Node* freeNode=0;
  while(uintptr_t(t->lastFree)>uintptr_t(t->nodes)) {
   t->lastFree=reinterpret_cast<Node*>(uintptr_t(t->lastFree)-sizeof(Node));
   if(t->lastFree->key.tag==0) { freeNode=t->lastFree; break; }
  }
  if(!freeNode) {
   // Original intentionally leaves the cursor one node below the array.
   t->lastFree=reinterpret_cast<Node*>(uintptr_t(t->lastFree)-sizeof(Node));
   vm.rehash(this,t,key);
   return vm.ensureValue(this,t,key);
  }
  Node* owner=vm.mainBucket(t,&bucket->key);
  if(owner!=bucket) {
   while(owner->next!=bucket) owner=owner->next;
   owner->next=freeNode;
   *freeNode=*bucket;
   bucket->next=0;
   bucket->value.tag=0; // payload intentionally survives relocation
  } else {
   freeNode->next=bucket->next;
   bucket->next=freeNode;
   bucket=freeNode;
  }
 }
 bucket->key.payload=key->payload;
 bucket->key.tag=key->tag;
 if(key->tag>=4 && (reinterpret_cast<const uint8_t*>(uintptr_t(key->payload))[5]&3)!=0
    && (t->header[5]&4)!=0) {
  t->header[5]&=uint8_t(~4u);
  t->gcLink=global->grayAgain;
  global->grayAgain=t;
 }
 return &bucket->value;
}
}
