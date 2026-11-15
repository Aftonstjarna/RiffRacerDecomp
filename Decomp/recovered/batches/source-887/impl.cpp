#include "impl.hpp"
namespace riff {
// Evidence: Game.exe [0x4f4d00,0x4f4d78). Callers include the unprotected
// failure paths of script_throw_status (0x4f4d80) and reallocate (0x4f7d10).
// This is state preparation before the panic callback, not exception dispatch.
void RIFF_REGISTER_CALL State::resetAfterError(int32_t status) {
    currentCall = baseCall;
    base = currentCall->base;
    closeUpvalues(this, base);
    // Reload base after closing: the original also reloads it for this call.
    setErrorObject(this, status, base);
    nestedCalls = baseNestedCalls;
    allowHook = 1;
    if (callCapacity > 20000) {
        // Helpers may relocate call-info storage. Use 32-bit address arithmetic
        // and signed division, matching the original stride calculation without
        // C++ subtraction between potentially distinct allocations.
        const int32_t delta = static_cast<int32_t>(
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(currentCall)) -
            static_cast<uint32_t>(reinterpret_cast<uintptr_t>(baseCall)));
        const int32_t used = delta / 24 + 1;
        if (used < 20000)
            resizeCallInfo(this, 20000);
    }
    errorFunction = 0;
    errorJump = 0;
}
}
