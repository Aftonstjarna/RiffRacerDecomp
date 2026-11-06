#include "impl.hpp"
namespace riff {
Record48* RIFF_THISCALL Record48::copyRetain(const Record48* source) {
    // Keep each load/store/retain before the next field load. In particular,
    // duplicate handles and self-copy each retain once per non-null slot.
    for (unsigned i = 0; i != 4; ++i) {
        RetainedHeader* value = source->retained[i];
        retained[i] = value;
        if (value) ++value->references; // non-atomic 32-bit modular increment
    }
    for (unsigned i = 0; i != 8; ++i) words[i] = source->words[i];
    return this;
}
}
