#ifndef WORKER_BYTE_VECTOR_HPP
#define WORKER_BYTE_VECTOR_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define WORKER_THISCALL __thiscall
#elif defined(__i386__)
#define WORKER_THISCALL __attribute__((thiscall))
#else
#define WORKER_THISCALL
#endif
// Original 32-bit layout: first, one-past-last, one-past-capacity.
struct WorkerByteVector {
    unsigned char* first;
    unsigned char* last;
    unsigned char* capacity_end;
    void WORKER_THISCALL append(const unsigned char* source);
    // External dependency at 0x519d50, requests at least count spare bytes.
    void WORKER_THISCALL grow(unsigned count);
};
#endif
