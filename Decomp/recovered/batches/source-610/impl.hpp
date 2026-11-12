#ifndef RIFF_BODY_RECORD_HPP
#define RIFF_BODY_RECORD_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
// VA 0x438560, 129 bytes. Field meanings beyond the construction context
// are unresolved; pointer-like arguments remain 32-bit original address tokens.
struct BodyConstructionRecord {
    float scalar;                       // +00, original XMM1 input
    uint32_t owner;                      // +04
    float basis[16];                     // +08, not a homogeneous identity
    uint32_t descriptor;                 // +48
    unsigned char vector[16];            // +4c, opaque bit-preserving copy
    float field5c, field60, field64, field68, field6c, field70;
    unsigned char flag74;
    unsigned char untouched75[3];
    float field78, field7c, field80, field84;
    BodyConstructionRecord* initialize(float value, uint32_t owner_token,
                                      uint32_t descriptor_token, const void* vector_source);
};
static_assert(sizeof(BodyConstructionRecord) == 0x88, "record size");
static_assert(offsetof(BodyConstructionRecord, descriptor) == 0x48, "descriptor offset");
static_assert(offsetof(BodyConstructionRecord, field84) == 0x84, "last field offset");
}
#endif
