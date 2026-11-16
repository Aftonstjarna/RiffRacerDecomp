#include "impl.hpp"
namespace riff {
uint32_t RIFF_FASTCALL ScriptState::finish_results(ScriptValue* first_result) {
    if (hook_mask & 2)
        first_result = script_return_hook(this, first_result);

    ScriptCallInfo* finished = call_info;
    call_info = finished - 1;
    const uint32_t requested = finished->requested_results;
    ScriptValue* destination = finished->function;
    base = call_info->base;
    saved_pc = call_info->saved_pc;

    // Use unsigned countdown for the original modulo-32-bit decrement. Negative
    // counts copy all available results; their remaining count is not padded.
    uint32_t remaining = requested;
    if (remaining != 0) {
        while (reinterpret_cast<uintptr_t>(first_result) <
               reinterpret_cast<uintptr_t>(top)) {
            // Forward, word-by-word copy is intentional: overlapping slots are
            // not a memmove, and the payload store precedes the tag load.
            destination->payload = first_result->payload;
            destination->tag = first_result->tag;
            ++destination;
            ++first_result;
            if (--remaining == 0)
                break;
        }
    }
    while (remaining != 0 && (remaining & 0x80000000u) == 0) {
        --remaining;
        destination->tag = 0;
        ++destination;
    }
    top = destination;
    // Callers test for zero to recognize requested_results == -1 (all results).
    return requested + 1u;
}
}
