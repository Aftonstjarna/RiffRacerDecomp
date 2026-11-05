#ifndef RIFF_WORKER_STATE_HPP
#define RIFF_WORKER_STATE_HPP
#include <stdint.h>
#include <stddef.h>

// Game.exe 0x4242e0, 150 bytes. No vtable or base constructor is present.
// Names describe storage only: gameplay meanings and non-float types remain unknown.
struct WorkerState {
    float values[24];                    // +0x000: IEEE binary32 0x3f19999a
    uint32_t zeroWordsA[24];              // +0x060
    uint32_t zeroWordsB[24];              // +0x0c0
    uint32_t stateWords[24];              // +0x120
    uint8_t flagBytes[36];                // +0x180
    struct Record { uint32_t words[3]; } records[12]; // +0x1a4
    WorkerState();
};
static_assert(sizeof(WorkerState) == 0x234, "original allocation size");
static_assert(offsetof(WorkerState, zeroWordsA) == 0x60, "layout");
static_assert(offsetof(WorkerState, zeroWordsB) == 0xc0, "layout");
static_assert(offsetof(WorkerState, stateWords) == 0x120, "layout");
static_assert(offsetof(WorkerState, flagBytes) == 0x180, "layout");
static_assert(offsetof(WorkerState, records) == 0x1a4, "layout");
#endif
