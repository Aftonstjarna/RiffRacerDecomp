#include "impl.hpp"
// Constructor-equivalent member: ECX is this and EAX returns this on i386.
// No old contents are read; callers must supply a writable record.
// Direct callers at 0x54451d, 0x544534 and 0x544540 initialize stack records.
// Adjacent destructor 0x5436f0 frees +8 and releases the object at +20;
// those observations do not establish complete field types or ownership.
ResourceRecord24* RR_THISCALL ResourceRecord24::construct() {
    fields[0] = 0;
    fields[1] = 0;
    fields[2] = 0;
    fields[3] = UINT32_MAX;
    fields[4] = 0;
    fields[5] = 0;
    return this;
}
