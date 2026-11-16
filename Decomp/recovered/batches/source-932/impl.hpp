#ifndef RIFF_SCRIPT_CALL_RESULT_FINISH_HPP
#define RIFF_SCRIPT_CALL_RESULT_FINISH_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_FASTCALL __attribute__((fastcall))
#endif
namespace riff {
// 32-bit Lua-style tagged stack value. A nil write changes tag only.
struct ScriptValue { uint32_t payload; uint32_t tag; };
struct ScriptCallInfo {
    ScriptValue* base;              // +00
    ScriptValue* function;          // +04: destination of returned values
    ScriptValue* limit;             // +08
    uint32_t saved_pc;              // +0c
    uint32_t requested_results;     // +10: signed count, normally -1 means all
    uint32_t tail_calls;            // +14
};
struct ScriptState {
    uint8_t unknown00[8];
    ScriptValue* top;               // +08: exclusive end of available results
    ScriptValue* base;              // +0c
    void* global;                   // +10
    ScriptCallInfo* call_info;      // +14
    uint32_t saved_pc;              // +18
    ScriptValue* stack_limit;       // +1c
    ScriptValue* stack;             // +20
    uint8_t unknown24[0x14];
    uint8_t hook_mask;              // +38: bit 1 requests return hook processing
    uint8_t unknown39[7];

    // Original 0x4f57a0: this in ECX, first_result in EDX, no stack arguments.
    uint32_t RIFF_FASTCALL finish_results(ScriptValue* first_result);
};
// Required external dependency: original 0x4f5680. It may relocate the stack,
// change state, and return a new first-result pointer. Its implementation is
// outside this recovery. No invented hook behavior is supplied here.
ScriptValue* RIFF_FASTCALL script_return_hook(ScriptState*, ScriptValue*);
#if UINTPTR_MAX == 0xffffffffu
static_assert(sizeof(ScriptValue) == 8, "value layout");
static_assert(sizeof(ScriptCallInfo) == 0x18, "call-info layout");
static_assert(offsetof(ScriptState, top) == 8, "top layout");
static_assert(offsetof(ScriptState, call_info) == 0x14, "frame layout");
static_assert(offsetof(ScriptState, hook_mask) == 0x38, "hook layout");
#endif
}
#endif
