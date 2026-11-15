#include "impl.hpp"
static_assert(sizeof(U32Vector) == 3 * sizeof(void*), "three pointer fields");
U32Vector* nested_vector12_range_assign(const U32Vector* first,
                                      const U32Vector* last,
                                      U32Vector* destination) {
    // Equality termination is deliberate: the original does not validate ranges.
    // Callers at 0x43e52b and 0x43e58e pass existing destination records.
    // This is assignment, not shallow record copying or construction.
    while (first != last) {
        destination->assign(*first);
        ++first;
        ++destination;
    }
    return destination;
}
