#ifndef WORKER_REFERENCE_RANGE_CLEAR_HPP
#define WORKER_REFERENCE_RANGE_CLEAR_HPP
#include <stdint.h>

// The object behind each entry has a displacement table pointer at +4.
// Its second 32-bit entry locates a reference-counted subobject relative
// to that pointer field. The surrounding types are not yet identified.
struct WorkerReferenceRange {
    void** begin;
    void** end;
    void** capacity_end;
    void clear();
};
#endif
