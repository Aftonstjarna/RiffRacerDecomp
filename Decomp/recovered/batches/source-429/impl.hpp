#ifndef RESOURCE_RECORD24_IMPL_HPP
#define RESOURCE_RECORD24_IMPL_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RR_THISCALL __thiscall
#elif defined(__i386__)
#define RR_THISCALL __attribute__((thiscall))
#else
#define RR_THISCALL
#endif
// Game.exe 0x5436c0, 44 bytes. Field meanings are not established.
// Fixed-width words preserve the original layout on Linux and Windows.
struct ResourceRecord24 {
    uint32_t fields[6];
    ResourceRecord24* RR_THISCALL construct();
};
static_assert(sizeof(ResourceRecord24) == 24, "original record size");
#endif
