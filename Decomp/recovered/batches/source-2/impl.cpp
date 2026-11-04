#include "impl.hpp"
// Original VA 0x44fcf0, 63 bytes. ECX=this, one callee-popped argument,
// EAX=this. Caller 0x44fb63 truncates a self-assignment to position+count
// before erasing the prefix. There is no allocation or capacity change.
extern "C" WideString* __attribute__((thiscall)) recovered_wide_truncate(
    WideString* self, WideSize new_length) {
    if (new_length > self->length)
        recovered_wide_out_of_range("invalid string position");
    self->length = new_length;
    WideUnit* data = self->capacity < 8
        ? self->storage.inline_data : self->storage.heap;
    data[new_length] = 0;
    return self;
}
