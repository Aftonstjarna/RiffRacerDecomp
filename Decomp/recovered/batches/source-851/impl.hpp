#ifndef SCRIPT_STREAM_IMPL_HPP
#define SCRIPT_STREAM_IMPL_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_CDECL __cdecl
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_CDECL __attribute__((cdecl))
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_CDECL
#define RIFF_THISCALL
#endif
// Original 32-bit layout at VA 0x4f5ff0: n, p, reader, data, state.
// The reader must set length when returning a non-null buffer. Buffer ownership
// stays with the reader; the stream neither allocates nor frees it.
struct ScriptStream {
    typedef const unsigned char* (RIFF_CDECL *Reader)(void* state, void* data, uint32_t* length);
    uint32_t remaining;
    const unsigned char* cursor;
    Reader reader;
    void* data;
    void* state;
    int RIFF_THISCALL refill();
};
#endif
