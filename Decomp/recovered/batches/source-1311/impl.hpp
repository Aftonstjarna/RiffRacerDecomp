#ifndef RECORD48_RANGE_HPP
#define RECORD48_RANGE_HPP
#include <stdint.h>
namespace riff {
struct RetainedHeader { uint32_t unknown; uint32_t references; };
struct Record48 { RetainedHeader* retained[4]; uint32_t words[8]; };
// Semantic interface: original VA 0x4b3eb0 uses ECX, EDX, and a
// caller-cleaned stack argument, an internal compiler convention.
Record48* record48_range_copy_retain(const Record48* first, const Record48* last, Record48* destination);
}
#endif
