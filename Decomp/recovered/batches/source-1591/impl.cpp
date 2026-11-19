#include "impl.hpp"

// 0x450c40, thiscall: base side effects happen before the kind test.
// Neither the input pointer nor the visual pointer is checked by the original.
void TextItem::set_colour(const float* value) {
    set_base_colour(value);
    if (kind != 3)
        visual->set_colour(value);
}
