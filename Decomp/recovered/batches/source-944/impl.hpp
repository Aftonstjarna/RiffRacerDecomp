#ifndef RIFF_READ_EXACT_HPP
#define RIFF_READ_EXACT_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#elif defined(__i386__)
#define RIFF_CDECL __attribute__((cdecl))
#else
#define RIFF_CDECL
#endif
struct AudioStream;
typedef int32_t (RIFF_CDECL *AudioRead)(AudioStream*, void*, uint32_t);
struct AudioBackend {
    uint32_t unknown0[2];
    AudioRead read;
};
struct AudioStream {
    uint8_t unknown0[0x6d3c];
    AudioBackend* backend;
};
static_assert(offsetof(AudioStream, backend)==0x6d3c, "backend offset");
#if defined(_M_IX86) || defined(__i386__)
static_assert(offsetof(AudioBackend, read)==8, "read slot");
#endif
extern "C" int32_t RIFF_CDECL audio_stream_read_exact(AudioStream*, void*, uint32_t);
#endif
