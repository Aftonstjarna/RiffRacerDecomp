#include "impl.hpp"
namespace riff {
WorkerServices worker_services = {0, 0, 0};
// Game.exe VA 0x48dbc0, RVA 0x8dbc0, 130 bytes; thiscall, ret 4,
// boolean result in AL. Accepted worker_thread.S agrees with direct disassembly.
// Base vtable 0x9fbe20 and decode-worker vtable 0x9fbdf0 use start at +4.
// The decode-worker constructor separately inlines similar creation behavior.
bool RR_THISCALL Worker::start(bool suspended) {
    handle = worker_services.begin(0, 0, worker_services.entry, this,
                                   suspended ? 4u : 0u, &thread_id);
    // Preserve the original's unusual sentinel; zero is considered success.
    if (handle == UINT32_MAX) return false;
    int32_t priority = 0;
    if (priority_mode == 0) priority = -1;
    else if (priority_mode == 2) priority = 1;
    worker_services.priority(handle, priority);
    return true; // SetThreadPriority failure is deliberately ignored.
}
}
