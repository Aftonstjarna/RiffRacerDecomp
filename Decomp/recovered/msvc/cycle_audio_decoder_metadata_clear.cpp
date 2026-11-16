class AudioDecoder {
    unsigned char decoderState[0x6f70];
    unsigned char metadataPresent;
    unsigned char alignment[3];
    // Preserve the observed individual 32-bit metadata writes and their order.
    volatile unsigned int metadata[14];
public:
    void clearMetadata();
};

void AudioDecoder::clearMetadata()
{
    metadataPresent = 0;
    metadata[0] = 0;
    metadata[1] = 0;
    metadata[2] = 0;
    metadata[3] = 0;
    metadata[4] = 0;
    metadata[5] = 0;
    metadata[7] = 0;
    metadata[6] = 0;
    metadata[9] = 0;
    metadata[8] = 0;
    metadata[11] = 0;
    metadata[10] = 0;
    metadata[13] = 0;
    metadata[12] = 0;
}
