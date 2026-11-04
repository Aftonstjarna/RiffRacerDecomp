#ifndef DECODE_WORKER_HPP
#define DECODE_WORKER_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RR_THIS __thiscall
#define RR_STD __stdcall
#define RR_CDECL __cdecl
#else
#define RR_THIS __attribute__((thiscall))
#define RR_STD __attribute__((stdcall))
#define RR_CDECL __attribute__((cdecl))
#endif
// Original 0x48d6e0, ECX=this, EAX=this, no stack arguments.
// Address tokens retain original ABI identity; they are not callable Linux code.
// Partial layout: only bytes through +0x14c are required by this constructor.
struct DecodeWorker {
    uint32_t vtable;
    uint32_t priority_mode;
    uint32_t thread_handle;
    uint32_t thread_id;
    uint8_t flag10;
    uint8_t untouched11[3];
    uint32_t request_event;
    uint32_t idle_event;
    uint8_t stop;
    uint8_t untouched1d[3];
    uint8_t string_storage[16];
    uint32_t string_size;
    uint32_t string_capacity;
    uint32_t request_output[5];
    uint8_t text[256];
    uint8_t second_text_first;
    DecodeWorker* RR_THIS initialize();
};
static_assert(offsetof(DecodeWorker, string_storage)==0x20, "SSO offset");
static_assert(offsetof(DecodeWorker, text)==0x4c, "text offset");
static_assert(offsetof(DecodeWorker, second_text_first)==0x14c, "second text offset");
typedef uint32_t (RR_STD *CreateEventFunction)(void*, int, int, const char*);
typedef uint32_t (RR_STD *WorkerEntry)(void*);
typedef uint32_t (RR_CDECL *BeginThreadFunction)(void*, uint32_t, WorkerEntry, void*, uint32_t, uint32_t*);
typedef int (RR_STD *SetPriorityFunction)(uint32_t, int);
#endif
