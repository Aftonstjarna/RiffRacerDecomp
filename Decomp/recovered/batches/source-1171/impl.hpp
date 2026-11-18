#ifndef PREPARE_CALLABLE_HPP
#define PREPARE_CALLABLE_HPP
#include <stdint.h>
struct Value { uint32_t payload, tag; };
struct State;
struct Services {
    const Value* (*lookup)(State*, Value*, uint32_t);
    void (*type_error)(State*, Value*);
    uint32_t (*reallocate)(State*, uint32_t, uint32_t, uint32_t);
    uint32_t (*size_error)(State*);
    void (*relocate)(State*, uint32_t);
};
struct State {
    uint32_t unknown00[2], top, base, global, frame, unknown18, limit, stack, unknown24, firstFrame, capacity;
    uint32_t unknown30[10], upvalues;
    Value* prepareCallable(Value* function, const Services& services);
};
#endif
