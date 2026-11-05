#ifndef RIFF_BUFFER_RELEASE_HPP
#define RIFF_BUFFER_RELEASE_HPP
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
struct ReleaseInterface;
typedef uint32_t (RIFF_STDCALL *InterfaceMethod)(ReleaseInterface*);
// Only slot 2 is recovered/used here; other interface methods are opaque.
struct ReleaseVtable { InterfaceMethod unused0, unused1, release; };
struct ReleaseInterface { const ReleaseVtable* vtable; };
// Seven DWORDs at original x86 offsets 0,4,8,12,16,20,24.
// Meanings of the last four words remain unresolved.
struct Buffer {
    ReleaseInterface* first;
    ReleaseInterface* second;
    ReleaseInterface* third;
    uint32_t state[4];
    void RIFF_THISCALL release();
};
}
#endif
