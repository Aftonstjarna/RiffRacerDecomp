#ifndef RIFF_STREAM_APPEND_HPP
#define RIFF_STREAM_APPEND_HPP
#include <stdint.h>
struct AudioChunk {
    unsigned char* data;
    int32_t length, capacity;
    AudioChunk* next;
};
struct AudioBuffer {
    AudioChunk* first;
    AudioChunk* last;
    int32_t length, cursor, saved_cursor;
    uint32_t unknown14;
    uint32_t allocation_size;
    uint32_t unknown1c;
    uint32_t free_count;
    AudioChunk* free_list;
    // Dependency at 0x58dfc0, not recovered in this bounded task.
    int32_t append(const void* source, int32_t count);
};
struct AudioStream {
    unsigned char unknown_prefix[0x6d7c];
    AudioBuffer buffer;
    unsigned char unknown6da4[8];
    unsigned char flags;
    unsigned char trailing[15];
    int32_t append_buffer(const void* source, int32_t count);
};
// Port integration point: original __iob_func()+0x40 (stderr FILE),
// fprintf with this exact format, line=769 and result=-1.
void audio_append_diagnostic(const char* format, int32_t line, int32_t result);
#endif
