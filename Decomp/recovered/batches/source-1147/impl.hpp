#ifndef WORKER_SLOT_RESET_HPP
#define WORKER_SLOT_RESET_HPP
#include <stdint.h>

// Layout inferred from accesses, not semantic names. Total stride: 0x1ac.
struct WorkerSlot {
    struct Triple { uint32_t begin, current, limit; } records[8];
    uint32_t unit_bits[3];
    uint32_t state[12];
    uint8_t unknown_09c[0x100];
    uint32_t tail_19c, tail_1a0;
    uint8_t flag_1a4, padding_1a5[3];
    uint32_t tail_1a8;
    void reset();
};
#endif
