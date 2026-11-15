#include "impl.hpp"
// Keep ordered scalar accesses: the original is a forward copy, not memmove.
// In particular a destination within a source propagates overwritten words.
Record40& RIFF_THISCALL Record40::operator=(const Record40& source) {
    words[0] = source.words[0];
    words[1] = source.words[1];
    words[2] = source.words[2];
    words[3] = source.words[3];
    words[4] = source.words[4];
    words[5] = source.words[5];
    words[6] = source.words[6];
    words[7] = source.words[7];
    words[8] = source.words[8];
    words[9] = source.words[9];
    return *this;
}
