#include "impl.hpp"
// 0x5c21d0: append all of right to left, then move the returned string into
// output. The append return value is used, even if it differs from left.
// Caller owns the output storage and the moved-from left remains valid.
NarrowString* worker_string_compose(NarrowString* output, NarrowString* left, const NarrowString* right) {
    NarrowString* appended = left->append_substring(right, 0, 0xffffffffu);
    output->move_construct(appended);
    return output;
}
