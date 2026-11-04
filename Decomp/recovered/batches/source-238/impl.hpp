#ifndef RIFF_WORKER_IMPL_HPP
#define RIFF_WORKER_IMPL_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#define RIFF_STDCALL __stdcall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#define RIFF_STDCALL __attribute__((stdcall))
#endif

// Recovered worker prefix; fields beyond this prefix are not needed here.
// Explicit vtable word preserves the original 32-bit layout without inventing
// virtual functions or implying that the original vtable is usable on Linux.
struct Worker {
    uint32_t vtable;
    uint32_t priority;
    uint32_t handle;
    uint32_t thread_id;
    void RIFF_THISCALL destroy();
};
#endif
