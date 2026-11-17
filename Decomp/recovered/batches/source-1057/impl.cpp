#include "impl.hpp"
namespace riff {
// 0x4f2560: callers at 0x4f4a76 and 0x5889bf pass the black parent
// in EDX and the white child on the stack. No precondition is checked here.
void State::forwardBarrier(Object* parent, Object* child) {
    Global* g = global;
    if (g->phase == 1) {
        markObject(g, child);
    } else {
        parent->marked = static_cast<uint8_t>((parent->marked & 0xf8u) | (g->currentWhite & 3u));
    }
}
}
