#include "impl.hpp"
namespace riff {
// Game.exe VA 0x457f70, RVA 0x57f70, 35 bytes. ECX=this, EAX=result,
// no stack arguments. Direct caller at 0x4980e3 passes its nonnull next;
// the null-link branch at 0x4980ea directly forms the same +0x1b0 address.
// No memory writes or external calls. Requires a valid, finite, null-ended
// chain; null this and invalid links fault in the original, cycles loop forever.
// No ownership, vector contents, or broader node semantics are inferred.
TerminalVectorStorage* RIFF_THISCALL Node::terminalVector() {
    Node* terminal = this;
    while (terminal->next != 0)
        terminal = terminal->next;
    return &terminal->terminal_vector;
}
}
