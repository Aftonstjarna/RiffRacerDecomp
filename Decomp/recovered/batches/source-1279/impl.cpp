#include "impl.hpp"
namespace riff {
namespace {
uint32_t& word(uint32_t p) { return *reinterpret_cast<uint32_t*>(static_cast<uintptr_t>(p)); }
uint8_t byte(uint32_t p) { return *reinterpret_cast<uint8_t*>(static_cast<uintptr_t>(p)); }
void visit_value(Collector* g, uint32_t value, int32_t tag) {
 if (tag >= 4 && (byte(value + 5) & 3)) services.mark(g, value);
}
}
// VA 004f1540: ECX is collector, EDX is thread. Frame and value pointers
// describe the original 32-bit VM address space; valid ranges are assumed.
void RF_FAST Collector::visit(Thread* t) {
 visit_value(this, t->special_value, t->special_tag);
 uint32_t end = t->top;
 for (uint32_t f=t->first_frame; f<=t->current_frame; f+=24)
  if (end < word(f+8)) end=word(f+8);
 uint32_t p=t->stack;
 while (p<t->top) { visit_value(this,word(p),static_cast<int32_t>(word(p+4))); p+=8; }
 while (p<=end) { word(p+4)=0; p+=8; }
 int32_t used=static_cast<int32_t>(end-t->stack)/8;
 int32_t n=t->frame_capacity;
 if (n>20000) return;
 int32_t count=static_cast<int32_t>(t->current_frame-t->first_frame)/24;
 if (count*4<n && n>16) {
  int32_t half=n/2;
  uint32_t old=t->first_frame;
  uint32_t result;
  if (static_cast<uint32_t>(half+1)<=0x0aaaaaaaU)
   result=services.resize(t,old,static_cast<uint32_t>(n)*24,static_cast<uint32_t>(half)*24);
  else result=services.too_large(t);
  int32_t offset=static_cast<int32_t>(t->current_frame-old)/24;
  t->first_frame=result; t->frame_capacity=half;
  t->current_frame=result+static_cast<uint32_t>(offset)*24;
  t->frame_limit=result+static_cast<uint32_t>(half-1)*24;
 }
 n=t->stack_capacity;
 if (static_cast<int32_t>(static_cast<uint32_t>(used)*4)<n && n>90) {
  int32_t half=n/2;
  uint32_t old=t->stack;
  uint32_t result;
  if (static_cast<uint32_t>(half+7)<=0x1fffffffU)
   result=services.resize(t,old,static_cast<uint32_t>(n)*8,static_cast<uint32_t>(half+6)*8);
  else result=services.too_large(t);
  t->stack=result; t->stack_capacity=half+6;
  t->stack_limit=result+static_cast<uint32_t>(half)*8;
  services.relocate(t,old);
 }
}
}
