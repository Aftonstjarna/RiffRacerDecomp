#ifndef RIFF_WORKER_DISPATCH_HPP
#define RIFF_WORKER_DISPATCH_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_STDCALL __stdcall
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_STDCALL __attribute__((stdcall))
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_STDCALL
#define RIFF_THISCALL
#endif
namespace riff {
// Original x86 vtable: deleting wrapper +0, start +4, worker body +8.
// Explicit deleting wrapper avoids GCC's two-slot virtual-destructor layout.
// Only the dispatch entry is recovered here; the other methods are contracts.
class Worker {
public:
    virtual Worker* RIFF_THISCALL deleting_wrapper(uint32_t flags) = 0;
    virtual bool RIFF_THISCALL start(bool suspended) = 0;
    virtual uint32_t RIFF_THISCALL run() = 0;
};
// Game.exe VA 0x0048dc50, RVA 0x8dc50, 15 bytes. _beginthreadex entry.
uint32_t RIFF_STDCALL worker_dispatch(void* argument);
}
#endif
