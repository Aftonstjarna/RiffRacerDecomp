#ifndef RIFF_GC_BARRIER_HPP
#define RIFF_GC_BARRIER_HPP
#include <stdint.h>
namespace riff {
struct Object { uint8_t opaque[4]; uint8_t type; uint8_t marked; };
struct Global { uint8_t opaque[20]; uint8_t currentWhite; uint8_t phase; };
struct State {
    uint8_t opaque[16]; Global* global;
    // Original uses ECX=this, EDX=parent, caller-popped child. The
    // portable member interface expresses semantics, not that hybrid ABI.
    void forwardBarrier(Object* parent, Object* child);
};
// Integration dependency at 0x4f0ef0: marks child using the global state.
void markObject(Global*, Object*);
}
#endif
