#ifndef RECORD24_COPY_HPP
#define RECORD24_COPY_HPP
#include <stdint.h>
// Original 0x4b3e40: ECX=first, EDX=last, [ESP+4]=destination;
// caller cleans stack; EAX returns destination advanced by the byte count.
// This compiler-internal register ABI is exposed here as a portable adapter.
unsigned char* record24_range_copy(const void* first, const void* last, void* destination);
#endif
