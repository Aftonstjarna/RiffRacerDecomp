#include "impl.hpp"
namespace riff {
static uint32_t address(const void* p) { return (uint32_t)(uintptr_t)p; }
static void* pointer(uint32_t p) { return (void*)(uintptr_t)p; }
void* State::returnHook(void* result, void (*dispatch)(State*,uint32_t,uint32_t), void (*resize)(State*,uint32_t)) {
 uint32_t resultOffset=address(result)-address(stack);
 dispatch(this,1,0xffffffffu);
 // function points to a tagged stack slot whose payload points to the closure.
 const uint8_t* closure=*(const uint8_t* const*)frame->function;
 if (closure[6]==0 && (hookMask&2)) {
  for (;;) {
   uint32_t count=frame->tailCalls;
   frame->tailCalls=count-1;
   if (!count) break;
   Hook callback=hook;
   if (callback && hookEnabled) {
    uint32_t topOffset=address(top)-address(stack);
    uint32_t limitOffset=address(frame->limit)-address(stack);
    Record record; record.event=4; record.argument=0xffffffffu; record.frameIndex=0;
    uint32_t freeBytes=address(stackLimit)-address(top);
    if (freeBytes<=0xa0u || freeBytes>=0x80000000u) {
     uint32_t n=capacity;
     resize(this,(n<20u || n>=0x80000000u)?n+20u:n*2u);
    }
    frame->limit=pointer(address(top)+0xa0u);
    hookEnabled=0;
    callback(this,&record);
    hookEnabled=1;
    frame->limit=pointer(address(stack)+limitOffset);
    top=pointer(address(stack)+topOffset);
   }
   if (!(hookMask&2)) break;
  }
 }
 return pointer(address(stack)+resultOffset);
}
}
