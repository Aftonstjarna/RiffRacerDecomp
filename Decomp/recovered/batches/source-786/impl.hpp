#ifndef RIFF_CAPACITY_HPP
#define RIFF_CAPACITY_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_FASTCALL __fastcall
#elif defined(__i386__)
#define RIFF_FASTCALL __attribute__((fastcall))
#else
#define RIFF_FASTCALL
#endif
// Original 0x4f0370..0x4f03d8: free helper, not a table member.
// Buckets are counts for capacities 1,2,4,...; total is replaced by capacity.
// Caller must supply enough buckets for the scan to terminate.
int32_t RIFF_FASTCALL choose_array_capacity(const int32_t* buckets, int32_t* total);
#endif
