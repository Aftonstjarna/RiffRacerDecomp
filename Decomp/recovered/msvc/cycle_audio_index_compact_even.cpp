struct AudioIndex {
    unsigned* entries;
    unsigned stride;
    unsigned extent;
    unsigned reserved;
    unsigned count;
    void compactEven();
};
void AudioIndex::compactEven() {
    if (count >= 2) {
        stride += stride;
        count >>= 1;
        for (unsigned i = 0; i < count; ++i)
            entries[i] = entries[i * 2];
        extent = count * stride;
    }
}
