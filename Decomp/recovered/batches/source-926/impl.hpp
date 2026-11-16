#ifndef RIFF_AUDIO_FRAME_HEADER_PLAUSIBLE_HPP
#define RIFF_AUDIO_FRAME_HEADER_PLAUSIBLE_HPP
#include <stdint.h>
namespace riff {
// Packed MPEG audio header, with sync in bits 31..21. Returns exactly 0 or 1.
int audio_frame_header_plausible(uint32_t header);
}
#endif
