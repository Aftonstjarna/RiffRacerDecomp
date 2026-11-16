#ifndef RIFF_AUDIO_STEREO_BRIDGE_HPP
#define RIFF_AUDIO_STEREO_BRIDGE_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#elif defined(__i386__)
#define RIFF_CDECL __attribute__((cdecl))
#else
#define RIFF_CDECL
#endif
namespace riff {
struct Decoder;
// Input and result words remain opaque: the bridge neither dereferences nor
// interprets them. Signed error codes, if any, are forwarded as bit patterns.
typedef uint32_t (RIFF_CDECL *AudioCallback)(uint32_t input, uint32_t channel,
                                          Decoder* decoder, uint32_t lane);
struct Decoder {
    unsigned char unknown[0x4cb4];
    AudioCallback selected_callback;
};
#if UINTPTR_MAX == 0xffffffffu
static_assert(offsetof(Decoder, selected_callback) == 0x4cb4, "original x86 layout");
#endif
uint32_t RIFF_CDECL audio_stereo_callback_bridge(uint32_t first_input,
                                                uint32_t second_input,
                                                Decoder* decoder);
}
#endif
