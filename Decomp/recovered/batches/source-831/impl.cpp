#include "impl.hpp"
namespace riff {
// These bindings deliberately retain the unresolved original dependencies.
// A Linux port must supply a compatible nonlocal-jump implementation and the
// separately recovered state-preparation helper; these are not OS emulations.
typedef void (RIFF_CDECL *LongJump)(void*, int);
typedef void (RIFF_FASTCALL *PrepareError)(ScriptState*, int32_t);
void RIFF_FASTCALL scriptThrowStatus(ScriptState* state, int32_t status)
{
    if (state->errorJump != 0) {
        state->errorJump->status = status;
        LongJump jump = *reinterpret_cast<LongJump volatile*>(uintptr_t(0x92d360));
        jump(state->errorJump->crtJumpBuffer, 1);
        // The real CRT longjmp does not return. A returning replacement is
        // outside the contract (the original would use caller-clobbered EDX).
    }
    state->status = static_cast<uint8_t>(status);
    if (state->global->panic != 0) {
        PrepareError prepare = reinterpret_cast<PrepareError>(uintptr_t(0x4f4d00));
        prepare(state, status);
        // Reload both global and callback: preparation can change the state.
        state->global->panic(state);
    }
    // Original returns when no panic handler exists, and also if panic returns.
    // In particular, no abort/exit is present in this 69-byte routine.
}
}
