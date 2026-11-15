#ifndef RIFF_CALLINFO_HPP
#define RIFF_CALLINFO_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
struct State;
// Integration seams for accepted VM helpers, not replacement allocator/error behavior.
struct Services {
    uint32_t (*reallocate)(State*, uint32_t, uint32_t, uint32_t);
    uint32_t (*too_large)(State*);
};
struct State {
    uint8_t unknown00[0x14];
    uint32_t current;                    // +14, CallInfo address
    uint8_t unknown18[12];
    uint32_t last;                       // +24, final allocated record
    uint32_t records;                    // +28, allocation base
    uint8_t unknown2c[4];
    uint32_t capacity;                   // +30, number of 24-byte records
    uint32_t resize_callinfo(uint32_t count, const Services& services);
};
static_assert(offsetof(State,current)==0x14,"VM layout");
static_assert(offsetof(State,records)==0x28,"VM layout");
static_assert(offsetof(State,capacity)==0x30,"VM layout");
}
#endif
