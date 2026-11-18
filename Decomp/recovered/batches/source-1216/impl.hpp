#ifndef WORKER_BYTE_VECTOR_ENSURE_SPARE_HPP
#define WORKER_BYTE_VECTOR_ENSURE_SPARE_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define WORKER_THISCALL __thiscall
#elif defined(__i386__)
#define WORKER_THISCALL __attribute__((thiscall))
#else
#define WORKER_THISCALL
#endif
struct WorkerByteVector {
    unsigned char* first;
    unsigned char* last;
    unsigned char* capacity_end;
    void WORKER_THISCALL ensure_spare(uint32_t count);
    // Original external dependency at 0x51a450.
    void WORKER_THISCALL reallocate(uint32_t capacity);
};
// Original imported std::length_error helper, called with the original message.
extern "C" void worker_byte_vector_length_error(const char* message);
#endif
