#include "impl.hpp"
namespace riff {
BodyConstructionRecord* BodyConstructionRecord::initialize(
    float value, uint32_t owner_token, uint32_t descriptor_token, const void* vector_source) {
    owner = owner_token;
    descriptor = descriptor_token;
    scalar = value;
    // Snapshot after the first three writes, before any subsequent stores.
    // This also preserves the original behavior when source aliases this record.
    unsigned char snapshot[16];
    const unsigned char* source = static_cast<const unsigned char*>(vector_source);
    for (unsigned i = 0; i < 16; ++i) snapshot[i] = source[i];
    field5c = 0.0f;
    field60 = 0.0f;
    for (unsigned i = 0; i < 16; ++i) vector[i] = snapshot[i];
    field64 = 0.5f;
    field68 = 0.0f;
    field6c = 0.8f;
    field70 = 1.0f;
    flag74 = 0;
    field78 = 0.005f;
    field7c = 0.01f;
    field80 = 0.01f;
    field84 = 0.01f;
    // Accepted matrix64-initialize-basis helper at 0x438480, inlined semantically.
    for (unsigned i = 0; i < 16; ++i)
        basis[i] = (i == 0 || i == 5 || i == 10) ? 1.0f : 0.0f;
    return this;
}
}
