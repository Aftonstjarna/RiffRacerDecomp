#include "impl.hpp"
namespace riff {
// Game.exe 004f4f50..004f4fca. Original ECX=this, EDX=count, no stack
// arguments. EAX also contains the final-record address on return. The caller
// at 004f4d00 shrinks capacities above 20000 after resetting current to base.
// The growth helper at 004f4fd0 doubles capacity; the call at 004f5b08
// also shrinks to 20000 during recovery. No record contents are accessed here.
// Addresses are explicit 32-bit VM words: no out-of-allocation C++ pointers
// are formed, including on zero count, null allocation, or wrapped inputs.
uint32_t State::resize_callinfo(uint32_t count, const Services& services) {
    const uint32_t old_base = records;
    uint32_t new_base;
    if (count + 1u <= 0x0aaaaaaau)
        new_base = services.reallocate(this, old_base, capacity * 24u, count * 24u);
    else
        new_base = services.too_large(this);
    // Original reloads current after the helper, but retains the old base.
    // Signed division truncates toward zero, even for malformed negative offsets.
    const uint32_t delta = current - old_base;
    const int32_t signed_delta = delta < 0x80000000u
        ? static_cast<int32_t>(delta) : -static_cast<int32_t>(~delta) - 1;
    const int32_t index = static_cast<int32_t>(signed_delta / 24);
    capacity = count;
    records = new_base;
    current = new_base + static_cast<uint32_t>(index) * 24u;
    last = new_base + (count - 1u) * 24u;
    return last;
}
}
