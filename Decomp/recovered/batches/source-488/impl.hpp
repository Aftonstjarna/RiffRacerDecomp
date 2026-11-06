#ifndef RIFF_SIGNED64_SHIFT_HPP
#define RIFF_SIGNED64_SHIFT_HPP
#include <stdint.h>
// Returns the shifted two's-complement bit pattern. Only count's low byte
// participates, matching CL in the original compiler helper.
uint64_t signed64_arithmetic_shift_right(uint64_t bits, uint32_t count);
#endif
