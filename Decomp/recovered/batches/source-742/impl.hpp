#ifndef RIFF_RANGE_ASSIGN_HPP
#define RIFF_RANGE_ASSIGN_HPP
#include <stdint.h>
struct U32Vector {
    uint32_t* begin;
    uint32_t* end;
    uint32_t* capacity_end;
    // Dependency: original vector copy assignment, VA 0x43e240.
    // Port integration supplies this member; it is outside this recovery.
    U32Vector& assign(const U32Vector& source);
};
// VA 0x43e7d0, 42 bytes. Original internal ABI: first in ECX,
// last in EDX, destination on caller-cleaned stack. Portable interface below.
U32Vector* nested_vector12_range_assign(const U32Vector* first,
                                      const U32Vector* last,
                                      U32Vector* destination);
#endif
