#ifndef RECORD24_IMPL_HPP
#define RECORD24_IMPL_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RECORD_THISCALL __thiscall
#elif defined(__i386__)
#define RECORD_THISCALL __attribute__((thiscall))
#else
#define RECORD_THISCALL
#endif
// Original x86 layout: begin +0, end +4, capacity_end +8.
// Record contents remain opaque. No ownership policy is invented here.
struct Record24Storage {
    unsigned char* begin;
    unsigned char* end;
    unsigned char* capacity_end;
    void RECORD_THISCALL append(const void* source);
    // External dependency: Game.exe 0x4b28d0, thiscall, ret 4.
    // Must preserve existing records and update these three pointers.
    // Its stack argument is the old end; full growth is not recovered here.
    void RECORD_THISCALL grow(unsigned char* old_end);
};
#endif
