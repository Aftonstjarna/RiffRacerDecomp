#ifndef RIFF_NARROW_ERASE_HPP
#define RIFF_NARROW_ERASE_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Port binding for std::_Xout_of_range. Must not return; the original throws.
extern "C" void narrow_out_of_range(const char* message);
struct NarrowString {
    union Storage { char local[16]; char* heap; } storage;
    uint32_t size;
    uint32_t capacity;
    NarrowString* RIFF_THISCALL erase(uint32_t offset, uint32_t count);
};
#endif
