#ifndef RIFF_WORKER_START_HPP
#define RIFF_WORKER_START_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RR_THISCALL __thiscall
#define RR_STDCALL __stdcall
#define RR_CDECL __cdecl
#else
#define RR_THISCALL __attribute__((thiscall))
#define RR_STDCALL __attribute__((stdcall))
#define RR_CDECL __attribute__((cdecl))
#endif
namespace riff {
typedef uint32_t (RR_STDCALL *ThreadEntry)(void*);
typedef uint32_t (RR_CDECL *BeginThread)(void*, uint32_t, ThreadEntry, void*, uint32_t, uint32_t*);
typedef int32_t (RR_STDCALL *SetPriority)(uint32_t, int32_t);
// Integration bindings: CRT _beginthreadex, Win32 SetThreadPriority, and the
// existing worker-dispatch entry (original VA 0x48dc50). Bind before start().
// Linux ports supply equivalent services; their internals are outside this task.
struct WorkerServices { BeginThread begin; SetPriority priority; ThreadEntry entry; };
extern WorkerServices worker_services;
class Worker {
public:
    // Original vtable slots +0, +4, +8. No implicit C++ virtual destructor.
    virtual Worker* RR_THISCALL deleting_wrapper(uint32_t flags) = 0;
    virtual bool RR_THISCALL start(bool suspended);
    virtual uint32_t RR_THISCALL run() = 0;
    uint32_t priority_mode; // x86 +4: 0 low, 1 normal, 2 high, others normal
    uint32_t handle;        // x86 +8
    uint32_t thread_id;     // x86 +12; written only by the CRT dependency
};
}
#endif
