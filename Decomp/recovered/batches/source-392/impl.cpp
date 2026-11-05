#include "impl.hpp"
namespace recovered {
// Free range algorithm, not a member: original ECX=begin, EDX=end,
// [entry ESP+4]=destination, EAX=result, caller removes stack arguments.
// application_frame at 0x4a10d1 passes a destination on the stack and stores
// the returned end at container +0x34 (begin is +0x30, stride 44).
Record44* copy_range(const Record44* begin, const Record44* end, Record44* destination) {
    while (begin != end) {
        destination->word0 = begin->word0;
        destination->word4 = begin->word4;
        destination->word8 = begin->word8;
        destination->word12 = begin->word12;
        destination->word16 = begin->word16;
        destination->word20 = begin->word20;
        destination->byte24 = begin->byte24;
        destination->word28 = begin->word28;
        destination->word32 = begin->word32;
        destination->word36 = begin->word36;
        destination->word40 = begin->word40;
        ++begin;
        ++destination;
    }
    return destination;
}
}
