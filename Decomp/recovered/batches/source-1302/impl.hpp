#ifndef RECORD40_COPY_HPP
#define RECORD40_COPY_HPP
#include <stdint.h>

// The payload's individual fields are not identified by this routine.
struct Record40 { uint32_t words[10]; };

// [first,last) must advance in whole records to reach last. Copying proceeds
// word by word in increasing address order, including for overlapping ranges.
Record40* record40_range_copy(const Record40* first, const Record40* last,
                              Record40* destination);
#endif
