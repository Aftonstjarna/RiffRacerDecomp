#ifndef RIFF_U64_SHIFT_LEFT_HPP
#define RIFF_U64_SHIFT_LEFT_HPP
#include <stdint.h>

// Portable interface to the register helper at VA 0x8f99a0 (RVA 0x4f99a0).
// Only the low byte of count is observed, just as the original observes CL.
// No memory is read or written. Arithmetic flags are outside this interface.
uint64_t u64_shift_left(uint64_t value, uint32_t count);
#endif
