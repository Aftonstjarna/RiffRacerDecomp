struct AudioStream {
    unsigned char unknown0[0x6d44];
    unsigned position;
    unsigned char unknown1[8];
    unsigned char flags;
    unsigned char unknown2[0x37];
    unsigned basePosition;
    unsigned char unknown3[4];
    unsigned bufferedPosition;
};

unsigned __cdecl audio_stream_query_position(AudioStream* stream)
{
    if (stream->flags & 8)
        stream->position = stream->bufferedPosition + stream->basePosition;
    return stream->position;
}
