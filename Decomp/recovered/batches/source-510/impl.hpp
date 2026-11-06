#ifndef RIFF_BYTE_RANGE_TRANSFORM_HPP
#define RIFF_BYTE_RANGE_TRANSFORM_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_CDECL __cdecl
#else
#define RIFF_CDECL __attribute__((cdecl))
#endif
namespace riff {
typedef int (RIFF_CDECL *ByteTransform)(int);
// VA 005C2740, 91 bytes. ECX points to a one-pointer output slot,
// EDX is begin; end, destination, callback are caller-cleaned stack args.
// This explicit semantic adapter avoids pretending that ABI is MS fastcall.
// No wider iterator/object layout is established by this routine.
uint8_t** transformBytes(uint8_t** result, const uint8_t* begin,
                         const uint8_t* end, uint8_t* destination,
                         ByteTransform callback);
}
#endif
