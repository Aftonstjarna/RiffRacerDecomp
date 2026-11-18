#ifndef WORKER_RECORD_RANGE_CLEAR_HPP
#define WORKER_RECORD_RANGE_CLEAR_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define WORKER_THISCALL __thiscall
#elif defined(__i386__)
#define WORKER_THISCALL __attribute__((thiscall))
#else
#define WORKER_THISCALL
#endif

// Layouts describe the 32-bit game. The names of the object and its table
// are unknown; the second table word is a signed adjustment to the owner.
struct WorkerReleaseOwner;
typedef void (WORKER_THISCALL *WorkerReleaseFunction)(WorkerReleaseOwner*, int);
struct WorkerOwnerTable { WorkerReleaseFunction release; };
struct WorkerReleaseOwner { WorkerOwnerTable* table; uint32_t references; };
struct WorkerObjectTable { uint32_t unknown; int32_t owner_offset; };
struct WorkerObject { WorkerObjectTable* table; };
struct WorkerRecord { WorkerObject* object; uint32_t payload[5]; };
struct WorkerRecordRange {
    WorkerRecord* begin;
    WorkerRecord* end;
    void clear();
};
#endif
