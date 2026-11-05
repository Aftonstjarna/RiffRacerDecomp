#include "impl.hpp"
namespace riff {
Record28** RIFF_THISCALL Record28Vector::erase_range(
    Record28** result, Record28* first, Record28* last) {
    // Full clear avoids touching the allocation, including empty allocations.
    if (first == begin && last == end) {
        end = begin;
    } else if (first != last) {
        Record28* destination = first;
        Record28* source = last;
        Record28* old_end = end;
        while (source != old_end) {
            *destination = *source;
            ++source;
            ++destination;
        }
        end = destination;
    }
    *result = first;
    return result;
}
// Valid inputs are ordered record boundaries in this vector's allocation.
// Like the original there are no bounds checks. The caller at 0x4a1090
// passes [begin + count*28, end) on the triple at application +0x24.
}
