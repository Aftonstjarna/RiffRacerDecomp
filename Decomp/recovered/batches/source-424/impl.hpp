#ifndef RECORD24_ROTATE_HPP
#define RECORD24_ROTATE_HPP
#include <stdint.h>
// Opaque record payload: no field types or ownership are established here.
// [first,middle) and [middle,last) must be adjacent valid 24-byte ranges,
// with nonnegative signed-32-bit byte distances. Unaligned storage is allowed.
void record24_rotate(unsigned char* first, unsigned char* middle, unsigned char* last);
#endif
