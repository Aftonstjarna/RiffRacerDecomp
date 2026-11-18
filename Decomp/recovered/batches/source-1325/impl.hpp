#ifndef WORKER_RECORD64_RANGE_HPP
#define WORKER_RECORD64_RANGE_HPP
#include <stdint.h>
// Addresses describe a half-open range of 64-byte records. The original uses
// ECX/EDX for the endpoints and a caller-cleaned stack destination argument.
// The portable adapter returns the destination advanced by the range length.
void* worker_record64_range_construct(const void* first, const void* last, void* destination);
#endif
