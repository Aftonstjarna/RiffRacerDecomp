#ifndef WORKER_RECORD84_MOVE_RANGE_HPP
#define WORKER_RECORD84_MOVE_RANGE_HPP
#include <stdint.h>
// Opaque record: observed size 0x54; individual field meanings are unknown.
struct WorkerRecord84 { unsigned char bytes[84]; };
// Forward copy into uninitialized storage. The original takes begin in ECX,
// end in EDX and destination on the stack, with caller stack cleanup.
WorkerRecord84* worker_record84_move_range(const WorkerRecord84* begin,
                                            const WorkerRecord84* end,
                                            WorkerRecord84* destination);
#endif
