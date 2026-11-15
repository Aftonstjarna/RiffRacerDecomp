#ifndef RIFF_REFERENCE_SLOT_VECTOR_HPP
#define RIFF_REFERENCE_SLOT_VECTOR_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
// The slot points to a subobject whose first word names an offset table.
// Only table[1] is established here: a signed byte offset to the ref base.
struct ReferenceSlot { const int32_t* base_offsets; };
struct ReferenceBase;
typedef void (RIFF_THISCALL *DeleteReference)(ReferenceBase*, uint32_t);
struct ReferenceBase {
    const DeleteReference* virtual_methods;
    uint32_t references;
};
struct ReferenceSlotVector {
    ReferenceSlot** begin;
    ReferenceSlot** end;
    ReferenceSlot** capacity_end;
    void RIFF_THISCALL remove_tail(uint32_t count);
};
}
#endif
