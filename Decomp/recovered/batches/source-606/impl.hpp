#ifndef RIFF_PATH_NORMALIZE_HPP
#define RIFF_PATH_NORMALIZE_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_STDCALL __stdcall
#elif defined(__i386__)
#define RIFF_STDCALL __attribute__((stdcall))
#else
#define RIFF_STDCALL
#endif
namespace riff {
// VS2013 narrow string layout observed at VA 0x43fd50. Ownership is external.
struct NarrowString {
    union Storage { char inline_data[16]; char* heap_data; } storage;
    uint32_t length;
    uint32_t capacity;
    char* data() { return capacity < 16 ? storage.inline_data : storage.heap_data; }
};
// Original is a free stdcall helper (stack argument, ret 4), not thiscall.
void RIFF_STDCALL normalize_path_slashes(NarrowString* path);
}
#endif
