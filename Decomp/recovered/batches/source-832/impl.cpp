#include "impl.hpp"
namespace riff {
// VA 0x486a30..0x486aaf. Direct callers at 0x486ad7, 0x486cf9,
// 0x487e48 and 0x4899cb prepare an error value then pass state in ECX.
// Helpers may transfer control nonlocally. Do not assume throwStatus cannot
// return: with neither protected jump nor panic it demonstrably does return.
void RIFF_THIS ScriptState::dispatchError() {
    if (errorHandlerOffset != 0) {
        Value* handler = reinterpret_cast<Value*>(
            reinterpret_cast<uintptr_t>(stackBase) +
            static_cast<uint32_t>(errorHandlerOffset));
        if (handler->tag != 6) throwStatus(this,5);
        // Keep the two word stores and reloads in their original order:
        // the handler can alias top or top-1; a cached Value changes behavior.
        Value* slot = top;
        slot->payload = (slot-1)->payload;
        slot->tag = (slot-1)->tag;
        slot = top;
        (slot-1)->payload = handler->payload;
        (slot-1)->tag = handler->tag;
        const uint32_t freeBytes = static_cast<uint32_t>(
            reinterpret_cast<uintptr_t>(stackLimit) -
            reinterpret_cast<uintptr_t>(top));
        if (static_cast<int32_t>(freeBytes) <= 8) {
            const uint32_t capacity = static_cast<uint32_t>(stackCapacity);
            const uint32_t next = stackCapacity < 1 ? capacity+1u : capacity+capacity;
            growStack(this,static_cast<int32_t>(next));
        }
        // Grow may relocate top. Handler itself is deliberately not reused.
        top = reinterpret_cast<Value*>(reinterpret_cast<uintptr_t>(top)+8u);
        callHandler(this,reinterpret_cast<Value*>(reinterpret_cast<uintptr_t>(top)-16u),1);
    }
    throwStatus(this,2);
}
}
