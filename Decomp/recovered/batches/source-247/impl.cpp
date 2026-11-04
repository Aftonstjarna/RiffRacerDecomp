#include "impl.hpp"
#include <stddef.h>
static_assert(offsetof(Worker, completionEvents)==0x460, "completion offset");
static_assert(offsetof(Worker, selected)==0x488, "selection offset");
static_assert(offsetof(Worker, pendingRequest)==0xba4, "request offset");
static_assert(offsetof(Worker, requestResult)==0xba8, "result offset");
// VA 0x4A1870, 135 bytes. Caller 0x52859c passes a stack request
// whose first word is ID 6. Payload interpretation belongs to the dispatcher.
uint8_t RR_THISCALL Worker::request(void* payload) {
    if (shuttingDown != 0) return 0;
    WaitForMultipleObjects(2, completionEvents, 1, UINT32_MAX);
    pendingRequest = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(payload));
    const uint32_t resetIndex = selected;
    requestResult = 0;
    requestActive = 1;
    ResetEvent(completionEvents[resetIndex]);
    SetEvent(workEvents[selected]);
    WaitForSingleObject(completionEvents[selected], UINT32_MAX);
    const uint8_t result = requestResult;
    requestActive = 0;
    return result;
}
