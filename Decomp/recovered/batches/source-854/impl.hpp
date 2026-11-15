#ifndef RIFF_INTERN_HPP
#define RIFF_INTERN_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct String {
    String* next;
    uint8_t type, mark, reserved, untouched;
    uint32_t hash, length;
    char* bytes() { return reinterpret_cast<char*>(this)+16; }
    const char* bytes() const { return reinterpret_cast<const char*>(this)+16; }
};
struct Global {
    String** buckets; uint32_t count, capacity;
    void* allocator; void* allocatorData;
    uint8_t white; uint8_t rest[107];
};
struct State;
struct Services {
    void* (*reallocate)(State*,void*,uint32_t,uint32_t);
    void (*resizeBuckets)(State*,uint32_t);
    // Original cdecl runtime_error(state, (char*)0x9fdb34); normally nonreturning.
    // Original text: "memory allocation error: block too big".
    void (*sizeError)(State*);
};
struct State {
    uint8_t unknown[16]; Global* global; uint8_t rest[80];
    // Original Game.exe [0x4f5e40,0x4f5fef). Callers at 0x441c6c,
    // 0x484874 and other VM string-push sites pass ECX=this, EDX=bytes, stack length;
    // the plain RET leaves length cleanup to the caller.
    // A portable member plus explicit dependency bindings models that ABI.
    String* intern(const char*,uint32_t,const Services&);
};
static_assert(sizeof(String)==16,"string header");
static_assert(offsetof(State,global)==16,"global offset");
static_assert(offsetof(Global,white)==20,"white offset");
}
#endif
