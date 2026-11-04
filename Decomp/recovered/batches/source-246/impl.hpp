#ifndef MEMBER_CLEANUP_HPP
#define MEMBER_CLEANUP_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RR_THISCALL __thiscall
#define RR_STDCALL __stdcall
#define RR_CDECL __cdecl
#else
#define RR_THISCALL __attribute__((thiscall))
#define RR_STDCALL __attribute__((stdcall))
#define RR_CDECL __attribute__((cdecl))
#endif
// Partial layout only: constructor 0x48d6e0 initializes more fields after +0x38.
// No virtual C++ destructor: vtable words below preserve original address tokens.
struct MemberCleanup {
    uint32_t vtable;
    uint32_t priority;
    uint32_t thread;
    uint32_t thread_id;
    uint8_t unknown10[4];
    uint32_t request_event;
    uint32_t idle_event;
    uint8_t stop;
    uint8_t unknown1d[3];
    union StringStorage { uint32_t heap; uint8_t inline_bytes[16]; } text;
    uint32_t text_size;
    uint32_t text_capacity;
    void RR_THISCALL cleanup();
};
static_assert(offsetof(MemberCleanup, stop)==0x1c, "stop layout");
static_assert(offsetof(MemberCleanup, text)==0x20, "string layout");
static_assert(sizeof(MemberCleanup)==0x38, "partial layout");
#endif
