#include "impl.hpp"
namespace riff {
// Original 0x4580a0 (90 bytes), ECX=this, one stack argument, ret 4.
// Caller 0x458012 passes old_size-new_size when shrinking. No bounds checks.
void RIFF_THISCALL ReferenceSlotVector::remove_tail(uint32_t count) {
    ReferenceSlot** const old_end = end;
    // The original shifts a 32-bit count by two, discarding its top two bits.
    // Scale the resulting slot distance to host pointer width for native ports.
    const uint32_t slot_distance = (count << 2) >> 2;
    ReferenceSlot** const new_end = reinterpret_cast<ReferenceSlot**>(
        reinterpret_cast<uintptr_t>(old_end) -
        static_cast<uintptr_t>(slot_distance) * sizeof(ReferenceSlot*));
    for (ReferenceSlot** slot = new_end; slot != old_end; ++slot) {
        ReferenceSlot* object = *slot;
        if (object) {
            ReferenceBase* base = reinterpret_cast<ReferenceBase*>(
                reinterpret_cast<unsigned char*>(object) + object->base_offsets[1]);
            // Unsigned arithmetic preserves DEC's wraparound (including 0 -> UINT_MAX).
            if (--base->references == 0)
                base->virtual_methods[0](base, 1);
        }
    }
    // Deliberately use captured bounds: callbacks may modify the vector/slots.
    // Removed slots are neither cleared nor freed by this routine.
    end = new_end;
}
}
