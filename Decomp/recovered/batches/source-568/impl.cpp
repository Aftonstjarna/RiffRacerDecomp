#include "impl.hpp"
namespace riff {
// Original callers 0x56b62b and 0x56b64f pass a source record and the
// container's end pointer as this, then advance that pointer by 0x44.
// They check destination for null; this routine itself has no null check.
// No vtable, allocation, reference counting, or exception registration occurs.
Record68* RIFF_THISCALL Record68::copy_construct(const Record68& source) {
    fields[0] = source.fields[0];
    fields[1] = source.fields[1];
    fields[2] = source.fields[2];
    fields[3] = source.fields[3];
    fields[4] = source.fields[4];
    fields[5] = source.fields[5];
    fields[6] = source.fields[6];
    fields[7] = source.fields[7];
    fields[8] = source.fields[8];
    fields[9] = source.fields[9];
    fields[10] = source.fields[10];
    fields[11] = source.fields[11];
    fields[12] = source.fields[12];
    // The original MOVDQU reads the whole tail before writing any of it.
    const Tail snapshot = source.tail;
    tail = snapshot;
    return this;
}
}
