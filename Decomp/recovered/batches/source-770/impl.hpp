#ifndef RIFF_RECORD52_HPP
#define RIFF_RECORD52_HPP
#include <stdint.h>
#include <stddef.h>
namespace riff {
// Layout recovered at VA 0x568200 (RVA 0x168200), 93 bytes.
// Offset names deliberately avoid assigning unproven gameplay meanings.
struct Record52 {
    float value00;
    uint32_t words04[6];
    uint32_t word1c;
    uint32_t word20;
    float values24[4];
    Record52* initialize();
};
static_assert(sizeof(Record52) == 52, "original record extent");
static_assert(offsetof(Record52, words04) == 4, "layout");
static_assert(offsetof(Record52, word1c) == 28, "layout");
static_assert(offsetof(Record52, word20) == 32, "layout");
static_assert(offsetof(Record52, values24) == 36, "layout");
}
#endif
