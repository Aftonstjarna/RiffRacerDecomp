#ifndef RIFF_AUDIO_FRAME_HEADERS_COMPATIBLE_HPP
#define RIFF_AUDIO_FRAME_HEADERS_COMPATIBLE_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_HEADER_CALL __fastcall
#elif defined(__i386__)
#define RIFF_HEADER_CALL __attribute__((fastcall))
#else
#define RIFF_HEADER_CALL
#endif
namespace riff {
// Scalar packed MPEG audio headers; ECX and EDX in the original x86 ABI.
// Returns exactly 0 or 1. Does not validate either header independently.
int RIFF_HEADER_CALL audio_frame_headers_compatible(uint32_t first, uint32_t second);
}
#endif
