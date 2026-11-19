#ifndef WORKER_VIEW_HEAP_PREPARE_HPP
#define WORKER_VIEW_HEAP_PREPARE_HPP
#include <stdint.h>

// Only the field accessed by the heap comparator is identified.
struct WorkerViewHeapItem {
    unsigned char unknown[0x188];
    int32_t key;
};

// The original receives the half-open pointer range in ECX and EDX.
#if defined(_MSC_VER)
#define WORKER_FASTCALL __fastcall
#elif defined(__i386__)
#define WORKER_FASTCALL __attribute__((fastcall))
#else
#define WORKER_FASTCALL
#endif
void WORKER_FASTCALL worker_view_heap_prepare(WorkerViewHeapItem** first,
                                              WorkerViewHeapItem** last);
#endif
