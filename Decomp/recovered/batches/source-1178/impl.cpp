#include "impl.hpp"
namespace riff {
static uint32_t addr(const void* p) { return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(p)); }
static void* ptr(uint32_t v) { return reinterpret_cast<void*>(static_cast<uintptr_t>(v)); }
void State::dispatchHook(uint32_t event, uint32_t argument, void (*resize)(State*,uint32_t)) {
 Hook callback=hook;
 if (!callback || !hookEnabled) return;
 uint32_t topOffset=addr(top)-addr(stack);
 uint32_t limitOffset=addr(currentFrame->limit)-addr(stack);
 HookRecord record;
 record.event=event; record.argument=argument;
 // Signed wrapped pointer difference, divided toward zero by 24.
 uint32_t difference=addr(currentFrame)-addr(firstFrame);
 int32_t signedDifference = difference < 0x80000000u ? static_cast<int32_t>(difference) : -1-static_cast<int32_t>(~difference);
 record.frameIndex=event==4 ? 0 : signedDifference/24;
 uint32_t freeBytes=addr(stackLimit)-addr(top);
 if (freeBytes<=0xa0u || freeBytes>=0x80000000u) {
  uint32_t capacity=stackCapacity;
  uint32_t requested=(capacity<20u || capacity>=0x80000000u) ? capacity+20u : capacity*2u;
  resize(this,requested);
 }
 currentFrame->limit=ptr(addr(top)+0xa0u);
 hookEnabled=0;
 callback(this,&record);
 hookEnabled=1;
 currentFrame->limit=ptr(addr(stack)+limitOffset);
 top=ptr(addr(stack)+topOffset);
}
}
