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
        unsigned char* entry = static_cast<unsigned char*>(*current++);
        if (entry) {
            unsigned char* base = entry + 4;
            int32_t* table = *reinterpret_cast<int32_t**>(base);
            unsigned char* control = base + table[1];
            uint32_t* count = reinterpret_cast<uint32_t*>(control + 4);
            if (--*count == 0) {
                WorkerRelease* vtable = *reinterpret_cast<WorkerRelease**>(control);
                vtable[0](control, 1);
            }
        }
    }
    end = begin;
}
void WorkerRecord::reset() {
    current_1 = start_1;
    current_2 = start_2;
    references.clear();
    current_3 = start_3;
    current_4 = start_4;
    current_5 = start_5;
    current_6 = start_6;
    cleared_5f8 = 0;
    cleared_5f4 = 0;
    value_600 = 0x80;
    value_5f0 = 0x3f800000u;
    for (int i = 0; i < 4; ++i) cleared_28c[i] = 0;
    cleared_29c = 0;
}
