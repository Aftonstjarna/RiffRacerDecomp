#ifndef RIFF_SCRIPT_STREAM_HPP
#define RIFF_SCRIPT_STREAM_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
// Inferred layout at 0x4f60a0; names describe use, not recovered debug names.
struct ScriptStream {
    typedef const unsigned char* (RIFF_CDECL *Reader)(void*, void*, uint32_t*);
    uint32_t available;                 // +0
    const unsigned char* cursor;        // +4 (32-bit original)
    Reader reader;                      // +8
    void* readerContext;                // +12, callback argument 2
    void* sourceContext;                // +16, callback argument 1
    uint32_t readBlock(void* destination, uint32_t requested);
};
#endif
