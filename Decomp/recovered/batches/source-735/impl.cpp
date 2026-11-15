#include "impl.hpp"
// Original uses ascending load/store pairs, including the first word (there
// is no separately installed vtable). Do not replace with memmove: overlapping
// machine-address ranges propagate earlier stores into subsequent loads.
// Valid readable source and writable destination storage are preconditions;
// no null, allocation, exception, or length handling exists in this routine.
Record88* RIFF_THISCALL Record88::copy_construct(const Record88& source) {
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
    words[10] = source.words[10];
    words[11] = source.words[11];
    words[12] = source.words[12];
    words[13] = source.words[13];
    words[14] = source.words[14];
    words[15] = source.words[15];
    words[16] = source.words[16];
    words[17] = source.words[17];
    words[18] = source.words[18];
    words[19] = source.words[19];
    words[20] = source.words[20];
    words[21] = source.words[21];
    return this;
}
