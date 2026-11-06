#ifndef RIFF_UTF16_TERMINATED_LENGTH_HPP
#define RIFF_UTF16_TERMINATED_LENGTH_HPP
#include <stdint.h>
// Original cdecl helper at VA 0x425bc0 (RVA 0x25bc0), 33 bytes.
// Input must point to readable 16-bit units through the first zero.
// Counts code units, not Unicode scalar values; no validation or writes.
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
extern "C" uint32_t RIFF_CDECL utf16_terminated_length(const uint16_t* text);
#endif
