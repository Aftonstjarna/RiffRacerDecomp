#include "impl.hpp"
namespace riff {
// Evidence: Game.exe [0x4f49b0,0x4f4aa2), accepted script_close_upvalues.S.
// Caller examples: 0x4851fa uses state+0x20 as level; 0x4f448e uses
// an interpreter register value. No return value is consumed.
static void unlinkOpen(Upvalue* u) {
    u->storage.open.previous->storage.open.next = u->storage.open.next;
    u->storage.open.next->storage.open.previous = u->storage.open.previous;
}
void RIFF_FASTCALL State::closeUpvalues(Value* level) {
    Global* const initialGlobal = global;
    while (openUpvalues && reinterpret_cast<uintptr_t>(openUpvalues->value) >=
                           reinterpret_cast<uintptr_t>(level)) {
        Upvalue* u = openUpvalues;
        openUpvalues = u->next;
        if ((static_cast<unsigned>(~initialGlobal->currentWhite) &
             (u->marked & 3)) != 0) {
            if (u->value != &u->storage.closed) unlinkOpen(u);
            reallocate(this, u, 20, 0);
        } else {
            unlinkOpen(u);
            // Keep the original two-word copy and ordering.
            u->storage.closed.payload = u->value->payload;
            u->storage.closed.tag = u->value->tag;
            u->value = &u->storage.closed;
            Global* g = global;
            u->next = g->root;
            g->root = u;
            if ((u->marked & 7) == 0) {
                if (g->gcPhase == 1) {
                    u->marked |= 4;
                    if (u->value->tag >= 4) {
                        void* child = reinterpret_cast<void*>(static_cast<uintptr_t>(u->value->payload));
                        if ((static_cast<uint8_t*>(child)[5] & 3) != 0)
                            barrier(this, u, child);
                    }
                } else {
                    u->marked = static_cast<uint8_t>((u->marked & 0xf8) | (g->currentWhite & 3));
                }
            }
        }
    }
}
}
