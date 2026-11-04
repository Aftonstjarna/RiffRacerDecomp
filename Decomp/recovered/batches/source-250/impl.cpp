#include "impl.hpp"
// The sole observed caller at 0x44e680 constructs this subobject at +0x130.
// Thread entry token 0x48dc50 dispatches vtable slot +8; dependencies remain
// reference helpers, not a reconstruction of decoding or OS thread behavior.
DecodeWorker* RR_THIS DecodeWorker::initialize() {
    thread_id = 0;
    priority_mode = 1;
    thread_handle = 0;
    vtable = 0x9fbdf0;
    flag10 = 0;
    stop = 0;
    string_capacity = 15;
    string_size = 0;
    string_storage[0] = 0;
    for (unsigned i = 0; i != 5; ++i) request_output[i] = 0;
    text[0] = 0;
    second_text_first = 0;
    // Original import table. A Linux integration must provide equivalent
    // services; these fixed bindings allow direct controlled oracle comparison.
    CreateEventFunction create_event = *reinterpret_cast<CreateEventFunction*>(0x92d114);
    request_event = create_event(0, 0, 0, 0);
    idle_event = (*reinterpret_cast<CreateEventFunction*>(0x92d114))(0, 1, 1, 0);
    thread_handle = (*reinterpret_cast<BeginThreadFunction*>(0x92d37c))(
        0, 0, reinterpret_cast<WorkerEntry>(0x48dc50), this, 0, &thread_id);
    // Preserve the original -1 test, including priority calls for NULL handles.
    if (thread_handle != UINT32_MAX) {
        int priority = 0;
        if (priority_mode == 0) priority = -1;
        else if (priority_mode == 2) priority = 1;
        (*reinterpret_cast<SetPriorityFunction*>(0x92d0d8))(thread_handle, priority);
    }
    return this;
}
