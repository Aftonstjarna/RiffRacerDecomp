#include "impl.hpp"
namespace riff {
namespace {
struct ReferenceBase;
typedef void* (RIFF_THISCALL *DeletingDestructor)(ReferenceBase*, unsigned);
struct ReferenceBase {
    DeletingDestructor* vtable;
    uint32_t references;
};
ReferenceBase* referenceBase(SharedObject* object) {
    return reinterpret_cast<ReferenceBase*>(
        reinterpret_cast<unsigned char*>(object) + 4 + object->virtualBaseTable[1]);
}
}
// Game.exe 0x490eb0..0x490ef8: ECX=this, one stack argument, ret 4.
// Caller 0x494491 supplies a newly constructed 0x240-byte object (ctor
// 0x512f80), or null after allocation failure. Its constructor confirms the
// vbtable at +4. No pointee type identity or full layout is inferred here.
void RIFF_THISCALL Owner::assign(SharedObject* incoming) {
    SharedObject* previous = slot214;
    if (previous == incoming) return;
    if (previous) {
        ReferenceBase* base = referenceBase(previous);
        // Unsigned arithmetic preserves x86 wraparound, including zero -> -1.
        if (--base->references == 0)
            base->vtable[0](base, 1);
    }
    // Keep this order: callbacks see the old slot; incoming's vbtable is read
    // only after the release callback and store, exactly as in the original.
    slot214 = incoming;
    if (incoming) ++referenceBase(incoming)->references;
}
}
