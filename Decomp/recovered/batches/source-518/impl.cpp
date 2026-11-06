#include "impl.hpp"
namespace riff {
uint64_t unsigned64_logical_shift_right(uint64_t value, uint8_t count)
{
    // The original checks the unsigned byte before executing masked x86 shifts.
    // Guarding here also avoids undefined C++ shifts by 64 or more.
    if (count >= 64)
        return 0;
    return value >> count;
}
}
// Evidence: original has no memory operands, stack arguments, object fields,
// imports or callees. For counts 32..63 it moves EDX into EAX, clears EDX,
// masks CL to 0..31 and shifts EAX. Counts 0..31 use SHRD/SHR.
// Direct caller at 0x597f80 sets CL=32 and stores EAX to [ESI+0x4c].
// Original also changes arithmetic flags, and masks CL for counts 32..63.
// These volatile machine-state effects are outside this portable value API.
