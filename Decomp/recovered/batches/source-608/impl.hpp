#ifndef RIFF_RECORD_RECYCLE_HPP
#define RIFF_RECORD_RECYCLE_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
// Original pointers are retained as 32-bit address tokens, never dereferenced.
// Adjacent 0x548b60 uses four pointer slots and parallel words at +0x10.
struct RecordPointerStack {
    uint32_t records[4];
    uint32_t parallel[4];
    uint32_t count;
};
struct RecordOwner {
    unsigned char unknown[0x158];
    uint32_t recycled[4];
    uint32_t recycle_count;
    uint32_t unknown_16c;
    uint32_t active_stack_address;
    void RIFF_THISCALL recycle(RecordPointerStack* stack);
};
static_assert(offsetof(RecordPointerStack, count) == 0x20, "source layout");
static_assert(offsetof(RecordOwner, recycle_count) == 0x168, "owner layout");
}
#endif
