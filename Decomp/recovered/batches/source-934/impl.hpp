#ifndef RIFF_AUDIO_MEMORY_READ_HPP
#define RIFF_AUDIO_MEMORY_READ_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
// Partial audio owner layout; preceding fields are deliberately opaque.
struct AudioMemoryState {
    unsigned char opaque[0x2c];
    const unsigned char* data;
    uint32_t length;
    uint32_t cursor;
};
#if UINTPTR_MAX == 0xffffffffu
static_assert(offsetof(AudioMemoryState, data) == 0x2c, "data offset");
static_assert(offsetof(AudioMemoryState, length) == 0x30, "length offset");
static_assert(offsetof(AudioMemoryState, cursor) == 0x34, "cursor offset");
#endif
extern "C" uint32_t RIFF_CDECL audio_memory_read_callback(AudioMemoryState*, void*, uint32_t);
#endif
