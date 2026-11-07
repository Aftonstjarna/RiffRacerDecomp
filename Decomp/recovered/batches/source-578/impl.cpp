#include "impl.hpp"
namespace riff {
// Game.exe 0x41dfb0..0x41dfd8: ECX=this, output and index on stack,
// callee removes 8 bytes, EAX=output. Callers at 0x41deb0, 0x41def0,
// 0x41df40 and 0x41e160 consume output+4, then record+8.
// 0xba2150 is the original reference dispatch table, not a relocated native
// vtable. Its implementation and the record's higher-level type are out of scope.
RecordReference32* RIFF_THISCALL RecordIndex32::index_reference(
    RecordReference32* output, uint32_t index) const {
    const uint32_t owner = owner_address;
    const uint32_t* metadata = reinterpret_cast<const uint32_t*>(
        static_cast<uintptr_t>(metadata_address));
    const uint32_t* storage = reinterpret_cast<const uint32_t*>(
        static_cast<uintptr_t>(owner));
    const uint32_t record = storage[3] + ((metadata[2] + index) << 5);
    // All input loads precede these stores, including when output aliases input.
    output->table_address = 0x00ba2150u;
    output->record_address = record;
    output->owner_address = owner;
    return output;
}
}
