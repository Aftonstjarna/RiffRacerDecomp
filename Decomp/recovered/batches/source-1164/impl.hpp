#ifndef WORKER_RECORD_RESET_HPP
#define WORKER_RECORD_RESET_HPP
#include <stdint.h>

struct WorkerReferenceRange {
    void** begin;
    void** end;
    void** capacity_end;
    void clear();
};
// Offsets are from the 32-bit game object; field meanings are not yet known.
struct WorkerRecord {
    uint8_t unknown_000[0x1c];
    uint32_t start_1, current_1;
    uint32_t unknown_024;
    uint32_t start_2, current_2;
    uint32_t unknown_030;
    WorkerReferenceRange references;
    uint32_t start_3, current_3, unknown_048;
    uint32_t start_4, current_4, unknown_054;
    uint32_t start_5, current_5, unknown_060;
    uint32_t start_6, current_6;
    uint8_t unknown_06c[0x220];
    uint32_t cleared_28c[4];
    uint8_t cleared_29c;
    uint8_t unknown_29d[0x353];
    uint32_t value_5f0, cleared_5f4;
    uint16_t cleared_5f8;
    uint8_t unknown_5fa[6];
    uint8_t value_600;
    void reset();
};
#endif
