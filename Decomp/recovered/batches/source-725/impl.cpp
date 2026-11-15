#include "impl.hpp"
namespace riff {
ReferenceBase* ReferenceView::base() {
    return reinterpret_cast<ReferenceBase*>(reinterpret_cast<char*>(this) +
                                            adjustments->base_displacement);
}
void ReferenceView::release() {
    ReferenceBase* owner = base();
    // Unsigned arithmetic preserves x86 wraparound, including a zero count.
    if (--owner->count == 0) owner->methods->destroy(owner, 1);
}
void ReferenceView::retain() { ++base()->count; }
ReferenceView** assign_reference_range(ReferenceView* const* first,
                                     ReferenceView* const* last,
                                     ReferenceView** output) {
    for (; first != last; ++first, ++output) {
        if (*output != *first) {
            if (*output) (*output)->release();
            // Deliberately reload after destruction: it may change the source.
            ReferenceView* incoming = *first;
            *output = incoming;
            if (incoming) incoming->retain();
        }
    }
    return output;
}
}
