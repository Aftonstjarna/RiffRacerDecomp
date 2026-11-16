#include "impl.hpp"
// Original stores in this order; there are no imports, allocation, cleanup,
// branches, SEH or return-value contract. Valid writable storage is required.
// In particular, this does not release old pointers before clearing the record.
// Direct callers at 0x58bf95 and 0x58c38d pass stack locals at EBP-0x24
// and EBP-0x28. The first continues using EAX from an earlier call: the
// original leaf happens to preserve EAX, but it does not return a C++ value.
// Adjacent cleanup at 0x58b300 handles +8/+0x14 separately; not recovered here.
void RIFF_THISCALL AudioMetadataState::initialize() {
    field_14 = 0;
    field_18 = 0;
    field_1c = 0;
    field_08 = 0;
    field_0c = 0;
    field_10 = 0;
    field_03 = 0;
    field_00 = 0;
    field_02 = 0;
}
