#include "impl.hpp"
namespace {
typedef uint32_t (RR_STDCALL *Wait)(uint32_t, uint32_t);
typedef int32_t (RR_STDCALL *HandleOperation)(uint32_t);
typedef void (RR_CDECL *Delete)(void*);
// Original IAT binding. A Linux port must bind these five operations to its
// synchronization/allocator layer; handle meaning is deliberately not invented.
template<class T> T import_at(uintptr_t address) {
    return *reinterpret_cast<T volatile*>(address);
}
}
// Game.exe 0x48d800..0x48d86a; thiscall, no stack arguments or local SEH.
// Called by 0x44eb10 at this+0x130 and deleting wrapper 0x48d7d0.
void RR_THISCALL MemberCleanup::cleanup() {
    vtable = 0x9fbdf0;
    import_at<Wait>(0x92d124)(idle_event, UINT32_MAX);
    stop = 1;
    import_at<HandleOperation>(0x92d104)(idle_event);
    import_at<HandleOperation>(0x92d120)(request_event);
    import_at<Wait>(0x92d124)(thread, UINT32_MAX);
    if (text_capacity >= 16u)
        import_at<Delete>(0x92d4b0)(reinterpret_cast<void*>(static_cast<uintptr_t>(text.heap)));
    text_capacity = 15;
    text_size = 0;
    text.inline_bytes[0] = 0;
    vtable = 0x9fbe20;
    import_at<HandleOperation>(0x92d0d4)(thread);
}
