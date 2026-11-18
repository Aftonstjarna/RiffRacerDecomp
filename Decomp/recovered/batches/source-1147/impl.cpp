#include "impl.hpp"

// VA 0x490d30, thiscall. The words may represent pointers or floats;
// retain their exact bits until the enclosing types are established.
void WorkerSlot::reset() {
    for (unsigned i = 0; i != 8; ++i)
        records[i].current = records[i].begin;
    for (unsigned i = 0; i != 3; ++i)
        unit_bits[i] = 0x3f800000u;
    for (unsigned i = 0; i != 12; ++i)
        state[i] = 0;
    tail_19c = 0;
    tail_1a0 = 0;
    flag_1a4 = 0;
    tail_1a8 = 0;
}
