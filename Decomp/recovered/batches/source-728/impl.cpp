#include "impl.hpp"
// Game.exe VA 0x59b370, RVA 0x19b370, 34 bytes. ECX is this;
// EAX returns all 32 bits. No arguments on the stack, stores, or calls.
// Direct callers at 0x5644ff and 0x56452d compare the result to stream IDs.
// The observed read order is 17,16,15,14. These are ordinary stable bytes,
// not MMIO. Valid input requires a readable object and header[14..17].
// No magic, length, null, or format checks are present in this accessor.
uint32_t RIFF_THISCALL PageHeaderView::stream_id_le32() const {
    uint32_t value = header[17];
    value = (value << 8) | header[16];
    value = (value << 8) | header[15];
    return (value << 8) | header[14];
}
