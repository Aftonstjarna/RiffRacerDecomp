#ifndef RIFF_BUFFER_PACK_HPP
#define RIFF_BUFFER_PACK_HPP
#include <stdint.h>
namespace riff {
// Observed 32-bit layout, not a recovered class name. +4 is unused here.
struct ByteBuffer {
    uint8_t* data;
    uint32_t unknown04;
    uint32_t size;
    void packHighThreeBytes();
};
}
#endif
