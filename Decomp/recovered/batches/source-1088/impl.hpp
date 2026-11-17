#ifndef RIFF_RECORD20_HPP
#define RIFF_RECORD20_HPP
#include <stdint.h>
struct Record20Vector {
    unsigned char* begin;
    unsigned char* end;
    unsigned char* capacity_end;
    // External original dependency at 0x52c7e0; reserves one spare record.
    void ensure_spare(unsigned char* position);
    void append(const void* source);
};
#endif
