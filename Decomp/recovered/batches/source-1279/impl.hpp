#ifndef RIFF_THREAD_GC_HPP
#define RIFF_THREAD_GC_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RF_FAST __fastcall
#else
#define RF_FAST __attribute__((fastcall))
#endif
namespace riff {
struct Thread;
// The implementation delegates the four original VM services to its embedding.
struct Services {
 void (*mark)(void*, uint32_t);
 uint32_t (*resize)(Thread*, uint32_t, uint32_t, uint32_t);
 uint32_t (*too_large)(Thread*);
 void (*relocate)(Thread*, uint32_t);
};
struct Thread {
 uint32_t unknown00[2], top, base, global, current_frame, unknown18;
 uint32_t stack_limit, stack, frame_limit, first_frame;
 int32_t stack_capacity, frame_capacity;
 uint32_t unknown34[5], special_value;
 int32_t special_tag;
 uint32_t unknown50[2], open_upvalues;
};
struct Collector {
 void RF_FAST visit(Thread* thread);
};
// Binding is supplied by the host; helpers are outside this recovery's scope.
extern const Services services;
}
#endif
