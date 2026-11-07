#ifndef RIFF_BYTE_WIDEN_TERMINATED_HPP
#define RIFF_BYTE_WIDEN_TERMINATED_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
// Byte capacity is halved (rounding down). Even capacities below two cause
// a two-byte terminator write: destination must always have that much storage.
// No decoding/code page conversion. Source must be readable even at size zero.
extern "C" void RIFF_CDECL recovered_byte_widen_terminated(
    uint16_t* destination, const unsigned char* source, uint32_t destination_bytes);
#endif
