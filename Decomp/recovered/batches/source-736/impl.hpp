#ifndef RIFF_RECORD32_HPP
#define RIFF_RECORD32_HPP
#include <stdint.h>
// Original 0x520c40..0x520c8c. Records have 32 bytes; field meanings unknown.
// begin/end must describe a reachable, forward range with 32-byte steps.
// This portable entry exposes semantics, not the custom ECX/EDX/stack ABI.
void* record32_copy_construct_range(const void* begin, const void* end, void* destination);
#endif
