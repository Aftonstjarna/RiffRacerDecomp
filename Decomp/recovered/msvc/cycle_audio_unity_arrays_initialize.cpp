struct AudioUnityArrays {
    unsigned char preceding[0x2448];
    unsigned state;
    float values[64];
    void initialize();
};
void AudioUnityArrays::initialize() {
    state = 0;
    float* value = values;
    unsigned remaining = 32;
    do {
        value[32] = 1.0f;
        value[0] = 1.0f;
        ++value;
    } while (--remaining);
}
