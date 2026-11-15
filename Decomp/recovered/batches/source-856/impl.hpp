#ifndef RIFF_BUCKETS_HPP
#define RIFF_BUCKETS_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct String {
    String* next;
    uint8_t type, mark, reserved, untouched;
    uint32_t hash, length;
};
struct Global {
    String** buckets; uint32_t strings, capacity;
    void* (*allocator)(void*,void*,uint32_t,uint32_t);
    void* allocatorData;
    uint8_t white, gcState;
    uint8_t unknown22[46];
    uint32_t allocatedBytes;
    uint8_t unknown72[56];
};
struct State;
struct Services {
    void* (*reallocate)(State*,void*,uint32_t,uint32_t);
    // Original reports "memory allocation error: block too big" and returns
    // null if the error handler returns. Usually this path does not return.
    void* (*allocationTooLarge)(State*);
};
struct State {
    uint8_t unknown[16]; Global* global; uint8_t rest[80];
    // Game.exe 0x4f5d70..0x4f5e40: ECX=this, EDX=count, plain RET.
    // Services is an explicit portable dependency adapter, not an original field.
    void resizeStringBuckets(uint32_t count,const Services& services);
};
static_assert(sizeof(void*)==4,"original data layout requires 32-bit pointers");
static_assert(offsetof(String,hash)==8,"hash offset");
static_assert(offsetof(Global,gcState)==21,"GC state offset");
static_assert(offsetof(Global,allocatedBytes)==68,"allocation accounting offset");
static_assert(offsetof(State,global)==16,"global state offset");
}
#endif
