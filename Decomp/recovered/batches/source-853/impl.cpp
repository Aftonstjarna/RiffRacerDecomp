#include "impl.hpp"
namespace riff {
void State::pushTerminated(const char* text,const PushServices& services) {
    // Save BEFORE interning; helpers may mutate the state. No null special case.
    Slot* destination=top;
    const char* end=text;
    while(*end) ++end;
    const uint32_t length=static_cast<uint32_t>(end-text);
    destination->payload=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(services.intern(this,text,length)));
    destination->tag=4;
    // x86 SUB/CMP/JG treats the wrapped byte difference as signed.
    const uint32_t freeBytes=static_cast<uint32_t>(reinterpret_cast<uintptr_t>(stackLimit)-reinterpret_cast<uintptr_t>(top));
    if(freeBytes<=8u || freeBytes>=0x80000000u) {
        const uint32_t capacity=stackCapacity;
        // Signed capacity < 1, with modulo arithmetic on both branches.
        const uint32_t requested=(capacity==0 || capacity>=0x80000000u)?capacity+1u:capacity+capacity;
        services.resize(this,requested);
    }
    // Use the relocated/current top, not the saved destination.
    top=reinterpret_cast<Slot*>(reinterpret_cast<uintptr_t>(top)+8u);
}
}
