#include "impl.hpp"

// Thiscall member, one pointer argument; the original returns with ret 4.
// Unordered comparisons trigger the copy, just like unequal components.
void Visual::set_colour(const float* value) {
    const float first = value[0];
    if (colour[0] != first || colour[1] != value[1] ||
        colour[2] != value[2] || colour[3] != value[3]) {
        colour[0] = first;
        colour[1] = value[1];
        colour[2] = value[2];
        colour[3] = value[3];
        flags |= 0x100;
    }
}
