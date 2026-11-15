#ifndef RIFF_RECORD520_HPP
#define RIFF_RECORD520_HPP
#include <stdint.h>
namespace riff {
// Raw record storage: no field types or ownership semantics are established.
// Range must reach last by 520-byte steps; accessible storage is caller-owned.
unsigned char* construct_record520_range(const unsigned char* first,
    const unsigned char* last, unsigned char* destination);
}
#endif
