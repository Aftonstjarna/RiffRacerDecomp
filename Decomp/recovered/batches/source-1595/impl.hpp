#ifndef RIFF_UNICODE_SCALAR_CP1252_MAP_HPP
#define RIFF_UNICODE_SCALAR_CP1252_MAP_HPP
#include <stdint.h>
// Maps the special Unicode code points to their CP1252 byte values. All
// other 32-bit values are returned unchanged, including invalid scalars.
uint32_t unicode_scalar_cp1252_map(uint32_t scalar);
#endif
