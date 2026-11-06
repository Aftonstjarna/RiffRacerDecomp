#ifndef RIFF_PE_SECTION_LOOKUP_HPP
#define RIFF_PE_SECTION_LOOKUP_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
// Returns a pointer into image, or null. image must cover all headers read.
// No PE signatures, bounds, section flags, or raw-file extents are validated.
extern "C" const unsigned char* RIFF_CDECL pe_section_lookup(
    const void* image, uint32_t relative_virtual_address);
#endif
