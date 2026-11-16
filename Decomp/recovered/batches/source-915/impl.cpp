#include "impl.hpp"
namespace riff {
// Game.exe 0x557510..0x557549: ECX=context, EDX=signed target, no stack args.
// Caller at 0x557904 zero-extends a saved scope byte into EDX.
// This register convention is modeled as a fastcall member, not thiscall.
// No allocation, destruction, or clearing of index entries occurs.
void RIFF_FASTCALL Compiler::remove_active_locals(int32_t target) {
    Function* current = function;
    while (static_cast<int32_t>(current->active_count) > target) {
        --current->active_count;
        const uint16_t index = current->active_indices[current->active_count];
        current->symbols->locals[index].end_position = current->position;
    }
}
// Negative targets never terminate for ordinary nonaliasing storage: the count
// wraps modulo 256. Pointers and indices are unchecked, as in the original.
}
