struct Value { unsigned low, high; };
struct Upvalue { Upvalue* next; unsigned tag; Value* value; };
struct Frame { Value* base; Value* function; Value* top; unsigned other[3]; };
struct State {
    unsigned header[2];
    Value* top;
    Value* base;
    unsigned field10;
    Frame* current;
    unsigned field18[2];
    Value* stack;
    unsigned field24;
    Frame* frames;
    unsigned field2c[11];
    Upvalue* open;
};
void __fastcall relocate(State* state, Value* oldStack) {
    state->top = state->stack + (state->top - oldStack);
    for (Upvalue* up = state->open; up; up = up->next)
        up->value = state->stack + (up->value - oldStack);
    for (Frame* frame = state->frames; frame <= state->current; ++frame) {
        frame->top = state->stack + (frame->top - oldStack);
        frame->base = state->stack + (frame->base - oldStack);
        frame->function = state->stack + (frame->function - oldStack);
    }
    state->base = state->stack + (state->base - oldStack);
}
