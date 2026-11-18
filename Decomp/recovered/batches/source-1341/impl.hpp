#ifndef WORKER_RECORD40_TRANSFER_HPP
#define WORKER_RECORD40_TRANSFER_HPP
#include <stdint.h>
// The record contents have not been identified. The original uses a custom
// ECX/EDX/stack calling convention; this is a portable semantic interface.
void* worker_record40_range_transfer(const void* begin, const void* end, void* destination);
#endif
