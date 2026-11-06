#ifndef RIFF_OWNER_SLOT214_HPP
#define RIFF_OWNER_SLOT214_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Original 32-bit object view. Names of the owning/pointee classes are unknown.
struct SharedObject {
    uint32_t unknown0;
    const int32_t* virtualBaseTable; // +4; entry 1 adjusts from this member
};
struct Owner {
    unsigned char unknown[0x214];
    SharedObject* slot214;
    void RIFF_THISCALL assign(SharedObject* incoming);
};
}
#endif
