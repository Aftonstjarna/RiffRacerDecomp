#include "impl.hpp"
namespace riff {
// VA 0x4f4fd0..0x4f501c, ECX=this, no arguments, EAX=new current.
// Callers 0x4f554e and 0x4f55f7 call only when current==last and use EAX
// as the newly selected record. This routine does not initialize that record.
// Dependencies may relocate/mutate state or leave nonlocally. Reload fields
// after calls; if an error helper returns, the original still advances.
uint32_t RIFF_METHOD State::grow() {
    const bool over_limit = capacity < 0x80000000u && capacity > 20000u;
    if (over_limit) {
        throw_status(this, 5);
    } else {
        resize_callinfo(this, capacity + capacity);
        if (capacity < 0x80000000u && capacity > 20000u)
            runtime_error(this, "stack overflow");
    }
    current += 24u;
    return current;
}
}
