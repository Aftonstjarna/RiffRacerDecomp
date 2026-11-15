#ifndef RIFF_RECORD520_COPY_HPP
#define RIFF_RECORD520_COPY_HPP
#include <stdint.h>
namespace riff {
// VA 0x416a20, 50 bytes. Opaque records: no field semantics established.
// Valid nonempty ranges reach last by increments of 520; storage must be valid.
// Forward copying is observable for overlap, unlike memmove. Assumes x86 DF=0.
// Original ABI: ECX=first, EDX=last, stack=destination, caller cleanup.
unsigned char* copy_record520_range(const unsigned char* first,
                                   const unsigned char* last,
                                   unsigned char* destination);
}
#endif
