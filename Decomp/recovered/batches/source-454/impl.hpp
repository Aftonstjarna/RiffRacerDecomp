#ifndef RIFF_BYTE_RANGE_COMPARE_HPP
#define RIFF_BYTE_RANGE_COMPARE_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
// Compare count bytes as unsigned values; return exactly -1, 0, or +1.
// Both ranges must be readable for count bytes. Zero count permits null pointers.
extern "C" int RIFF_CDECL byte_range_compare(const void* left, const void* right,
                                            uint32_t count);
#endif
