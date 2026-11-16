#ifndef RIFF_AUDIO_STREAM_SHIFT_BYTE_HPP
#define RIFF_AUDIO_STREAM_SHIFT_BYTE_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
namespace riff {
struct AudioStream;
typedef int32_t (RIFF_CDECL *ReadBytes)(AudioStream*, unsigned char*, int32_t);
struct AudioBackend {
    // Only the read slot is recovered; other entries remain opaque.
    void (RIFF_CDECL *unknown0)();
    void (RIFF_CDECL *unknown4)();
    ReadBytes read;
};
struct AudioStream {
    unsigned char unknown[0x6d3c];
    AudioBackend* backend;
};
// Original VA 0x58dad0, size 66; cdecl, NOT a thiscall member.
int32_t RIFF_CDECL audio_stream_shift_byte(AudioStream*, uint32_t* accumulator);
}
#endif
