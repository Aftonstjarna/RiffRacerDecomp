#ifndef RECOVERED_AUDIO_BUFFER_HPP
#define RECOVERED_AUDIO_BUFFER_HPP
#include <stdint.h>
struct AudioChunk {
    unsigned char* data;       // +0
    int32_t length;             // +4: populated bytes
    int32_t capacity;           // +8: not read by this routine
    AudioChunk* next;           // +12
};
struct AudioBuffer {
    AudioChunk* first;          // +0
    AudioChunk* last;           // +4: untouched
    int32_t length;             // +8: bytes represented by active chain
    int32_t cursor;             // +12
    int32_t saved_cursor;       // +16: restored on insufficient data
    uint32_t other[5];          // +20..+39: untouched, neighboring routines use these
    int32_t read_range(void* destination, int32_t count);
};
#endif
