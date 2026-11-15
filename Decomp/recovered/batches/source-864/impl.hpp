#ifndef RIFF_SCRIPT_STREAM_HPP
#define RIFF_SCRIPT_STREAM_HPP
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
// Observed 32-bit layout; names describe usage, not recovered debug names.
struct ScriptStream {
    typedef const uint8_t* (RIFF_CDECL *Reader)(void*, void*, uint32_t*);
    uint32_t remaining;             // +0
    const uint8_t* cursor;           // +4
    Reader reader;                  // +8
    void* readerArgument;            // +12
    void* readerContext;             // +16
    int RIFF_THISCALL peek();
};
#endif
