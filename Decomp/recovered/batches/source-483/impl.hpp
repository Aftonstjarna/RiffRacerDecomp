#ifndef RIFF_PE32_IMAGE_VALIDATE_HPP
#define RIFF_PE32_IMAGE_VALIDATE_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
// Original VA 0x8f9b40, 49 bytes. Caller owns all memory reached by reads.
extern "C" int RIFF_CDECL pe32_image_validate(const void* image);
#endif
