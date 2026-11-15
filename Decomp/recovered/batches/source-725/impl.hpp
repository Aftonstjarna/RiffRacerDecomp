#ifndef RIFF_REFERENCE_ASSIGN_HPP
#define RIFF_REFERENCE_ASSIGN_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
struct ReferenceBase;
typedef void* (RIFF_THISCALL *DestroyReference)(ReferenceBase*, unsigned);
struct LifetimeTable { DestroyReference destroy; };
// Only table word +4 is known: signed displacement from view to count owner.
struct AdjustmentTable { uint32_t unknown; int32_t base_displacement; };
struct ReferenceBase { const LifetimeTable* methods; uint32_t count; };
struct ReferenceView {
    const AdjustmentTable* adjustments;
    ReferenceBase* base();
    void release();
    void retain();
};
// Original 0x43efd0, 86 bytes: ECX=first, EDX=last, stack=output,
// caller cleanup. This portable adapter does not claim that private ABI.
ReferenceView** assign_reference_range(ReferenceView* const* first,
                                     ReferenceView* const* last,
                                     ReferenceView** output);
}
#endif
