#ifndef RECORD56_TRANSFER_HPP
#define RECORD56_TRANSFER_HPP
#include <stdint.h>
// Transfers [first,last) in 56-byte strides and returns the advanced destination.
// Records have 54 copied bytes and two destination bytes left untouched.
void* record56_range_transfer(const void* first, const void* last, void* destination);
#endif
