#include "impl.hpp"
#include <stddef.h>
static_assert(offsetof(Worker, handle) == 8, "original handle offset");
static_assert(sizeof(Worker) == 16, "known worker prefix");
#ifdef _MSC_VER
extern "C" __declspec(dllimport) int RIFF_STDCALL CloseHandle(void* handle);
#else
extern "C" int RIFF_STDCALL CloseHandle(void* handle);
#endif

// Game.exe 0x0048DBB0, 16 bytes. Non-deleting destructor body (this in ECX).
// Original vtable 0x009FBE20 contains delete/start/purecall slots. Nearby
// scalar-deleting destructor 0x0048DB80 performs the same reset/close then
// optionally frees memory. This routine never frees, waits, or clears handle.
// Cleanup thunks at 0x008FF939 (+0x14), 0x00906E58 (+4), and
// 0x00907C40 (+0) establish use on embedded and base worker subobjects.
// Return is semantically void; EAX happens to retain CloseHandle's result.
void RIFF_THISCALL Worker::destroy() {
    const uint32_t saved_handle = handle;
    vtable = 0x009FBE20u;
    CloseHandle(reinterpret_cast<void*>(static_cast<uintptr_t>(saved_handle)));
}
