#include "impl.hpp"
namespace riff {
// Original 0x5497b0..0x549811, ECX=this, no stack arguments; return unused.
// Direct caller at 0x54b115 passes stack workspace ebp-0x2864 after zeroing
// +0x2640, +0x2644, +0x2648 and +0x264c. This function itself retains the
// incoming free head/count. Neighbor 0x549780 removes nodes using +30/+34.
// Payload meanings, mode 9, and other workspace fields remain unidentified.
void RIFF_THISCALL CollisionWorkspace::linkFreeRecords() {
    mode = 9;
    for (unsigned i = 0; i != 4; ++i) cleared_28[i] = 0;
    cleared_38 = 0;
    cleared_263c = 0;
    for (unsigned remaining = 128; remaining != 0; --remaining) {
        CollisionRecord* record = &records[remaining - 1];
        record->previous = 0;
        record->next = free_head;
        if (free_head) free_head->previous = record;
        ++free_count; // unsigned wrap, as the original INC instruction
        free_head = record;
    }
}
}
