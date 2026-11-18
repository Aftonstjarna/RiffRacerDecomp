#include "impl.hpp"

#if defined(_MSC_VER)
#define WORKER_THISCALL __thiscall
#elif defined(__i386__)
#define WORKER_THISCALL __attribute__((thiscall))
#else
#define WORKER_THISCALL
#endif

typedef void (WORKER_THISCALL *WorkerRelease)(void*, unsigned);

void WorkerReferenceRange::clear() {
    void** current = begin;
    void** const last = end;
    while (current != last) {
        unsigned char* entry = static_cast<unsigned char*>(*current);
        if (entry) {
            unsigned char* base = entry + 4;
            int32_t* displacement_table = *reinterpret_cast<int32_t**>(base);
            unsigned char* control = base + displacement_table[1];
            uint32_t* count = reinterpret_cast<uint32_t*>(control + 4);
            --*count;
            if (*count == 0) {
                WorkerRelease* vtable = *reinterpret_cast<WorkerRelease**>(control);
                vtable[0](control, 1);
            }
        }
        ++current;
    }
    end = begin;
}
