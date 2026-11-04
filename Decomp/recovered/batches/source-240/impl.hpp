#ifndef WORKER_RECOVERY_HPP
#define WORKER_RECOVERY_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define WORKER_THISCALL __thiscall
#define WORKER_STDCALL __stdcall
#define WORKER_CDECL __cdecl
#else
#define WORKER_THISCALL __attribute__((thiscall))
#define WORKER_STDCALL __attribute__((stdcall))
#define WORKER_CDECL __attribute__((cdecl))
#endif
namespace recovered {
typedef int32_t (WORKER_STDCALL *CloseHandleImport)(uint32_t);
typedef void (WORKER_CDECL *DeleteImport)(void*);
// Port integration must bind these to CloseHandle and operator delete.
extern CloseHandleImport close_handle;
extern DeleteImport delete_storage;
struct Worker {
    uint32_t vtable_address; // Original 32-bit address, not a host C++ vptr.
    uint32_t priority;
    uint32_t handle;
    uint32_t thread_id;
    Worker* WORKER_THISCALL scalar_delete(uint32_t flags);
};
}
#endif
