#include "impl.hpp"
namespace riff {
namespace {
// Byte access permits overlap with count fields without violating C++ aliasing.
// All addressed bytes must exist; the original supplies no bounds validation.
uint32_t load_word(const unsigned char* p) {
    return uint32_t(p[0]) | (uint32_t(p[1]) << 8) |
           (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);
}
void store_word(unsigned char* p, uint32_t v) {
    p[0] = static_cast<unsigned char>(v);
    p[1] = static_cast<unsigned char>(v >> 8);
    p[2] = static_cast<unsigned char>(v >> 16);
    p[3] = static_cast<unsigned char>(v >> 24);
}
}
// Game.exe 0x548b30..0x548b58: ECX=this, one stack argument, ret 4.
// Calls at 0x548768 and 0x5487cb pass owner->active_stack_address.
// No allocation, clearing of popped slots, pointer dereference or return contract.
void RIFF_THISCALL RecordOwner::recycle(RecordPointerStack* stack) {
    --stack->count;
    const uint32_t source_index = stack->count;
    const uint32_t destination_index = recycle_count;
    const uint32_t record = load_word(reinterpret_cast<unsigned char*>(stack) + source_index * uint32_t(4));
    store_word(reinterpret_cast<unsigned char*>(this) + 0x158 + destination_index * uint32_t(4), record);
    ++recycle_count; // Reload: the preceding store can itself overwrite this count.
}
}
