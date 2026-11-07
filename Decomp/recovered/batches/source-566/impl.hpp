#ifndef RECORD36_COPY_RANGE_HPP
#define RECORD36_COPY_RANGE_HPP
#include <stdint.h>
namespace riff {
// Opaque record: no field meanings are established by this copy routine.
struct Record36 { unsigned char bytes[36]; };
// VA 0x422580, 57 bytes. Source range must end exactly on a 36-byte step.
// Returns the final destination address (the original's EAX, unused by caller).
uintptr_t copy_record36_range(const void* first, const void* last, void* destination);
}
#endif
