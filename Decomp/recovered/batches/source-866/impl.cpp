#include "impl.hpp"
namespace riff {
// Game.exe VA 0x4f6140..0x4f61a0. Custom original ABI: ECX=state,
// EDX=buffer, caller-cleaned stack requested; portable member ownership here.
// Caller 0x55602f requests a serialized string's byte count then reads into
// the returned pointer. No terminator is stored by this routine.
void* ScriptBuffer::ensure_capacity(ScriptState* state, uint32_t requested,
                                    const BufferServices& services) {
    const uint32_t old_capacity = capacity;
    if (requested <= old_capacity) return data;
    if (requested < 32) requested = 32;
    // Deliberately preserve the original unsigned wrap, including UINT32_MAX.
    if (uint32_t(requested + uint32_t(1)) > 0xfffffffdu) {
        services.runtime_error(state, "memory allocation error: block too big");
        // Normally error transfer does not return. These stores are present
        // in the original and matter if the error service does return.
        capacity = requested;
        data = 0;
        return 0;
    }
    void* result = services.reallocate(state, data, old_capacity, requested);
    data = result;
    capacity = requested;
    return result;
}
}
