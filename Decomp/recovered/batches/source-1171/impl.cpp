#include "impl.hpp"
#include <stdint.h>
// VA 0x4f5380: ECX state, EDX stack slot. Dependencies remain explicit.
// VM addresses and arithmetic are 32-bit, as in the original executable.
Value* State::prepareCallable(Value* function, const Services& s) {
    const Value* method = s.lookup(this, function, 16);
    uint32_t offset = uint32_t(reinterpret_cast<uintptr_t>(function)) - stack;
    if (method->tag != 6) s.type_error(this, function);
    uint32_t cursor = top, target = uint32_t(reinterpret_cast<uintptr_t>(function));
    while (cursor > target) {
        Value* dst = reinterpret_cast<Value*>(uintptr_t(cursor));
        Value* src = reinterpret_cast<Value*>(uintptr_t(cursor - 8));
        dst->payload = src->payload;
        dst->tag = src->tag;
        cursor -= 8;
    }
    if (int32_t(limit - top) <= 8) {
        uint32_t old = stack, count = capacity;
        uint32_t usable = int32_t(count) >= 1 ? count * 2 : count + 1;
        uint32_t allocated = usable + 6;
        uint32_t replacement = allocated + 1 > 0x1fffffffu
            ? s.size_error(this) : s.reallocate(this, old, count * 8, allocated * 8);
        stack = replacement;
        capacity = allocated;
        limit = replacement + usable * 8;
        s.relocate(this, old);
    }
    top += 8;
    Value* dst = reinterpret_cast<Value*>(uintptr_t(stack + offset));
    dst->payload = method->payload;
    dst->tag = method->tag;
    return dst;
}
