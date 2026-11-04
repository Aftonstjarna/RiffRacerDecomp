#include "impl.hpp"
namespace riff {
uint32_t RIFF_STDCALL worker_dispatch(void* argument) {
    // No validation or field accesses beyond the virtual dispatch. The original
    // forwards EAX unchanged and pops its single four-byte stack argument.
    return static_cast<Worker*>(argument)->run();
}
}
