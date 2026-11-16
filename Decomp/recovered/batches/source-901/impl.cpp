#include "impl.hpp"
namespace riff {
// Original VA 0x4f4c40, size 67. The internal calling convention uses ECX
// for the prototype, EDX for ordinal, and a caller-popped position argument.
// The public member interface intentionally uses the platform's normal ABI.
const char* ScriptPrototype::local_name(uint32_t ordinal, int32_t position) const {
    for (int32_t i = 0; i < local_count; ++i) {
        const ScriptLocal& local = locals[i];
        // Early exit is observable even with an unsorted input table.
        if (local.start_position > position)
            break;
        if (position < local.end_position && --ordinal == 0) {
            // Integer addition preserves the original address-only operation,
            // including null name_object -> address 16; no string is read.
            return reinterpret_cast<const char*>(
                reinterpret_cast<uintptr_t>(local.name_object) + uintptr_t(16));
        }
    }
    return 0;
}
}
