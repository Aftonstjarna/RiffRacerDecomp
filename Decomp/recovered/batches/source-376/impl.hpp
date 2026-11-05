#ifndef RIFF_RECORD28_IMPL_HPP
#define RIFF_RECORD28_IMPL_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// Field meanings are unresolved. Assignment copies all 28 bytes without
// destruction, ownership transfer, allocation, or clearing the vacated tail.
struct Record28 { uint32_t words[7]; };
struct Record28Vector {
    Record28* begin;
    Record28* end;
    Record28* capacity_end;
    // VA 0x4b2480, 116 bytes. Explicit output slot models the original
    // iterator-result storage. EAX returns that slot; callee pops 12 bytes.
    Record28** RIFF_THISCALL erase_range(Record28** result,
                                        Record28* first, Record28* last);
};
}
#endif
