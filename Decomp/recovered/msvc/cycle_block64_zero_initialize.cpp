struct Block64 {
    volatile unsigned words[16];
    Block64();
};

Block64::Block64() {
    words[0] = 0;
    words[1] = 0;
    words[2] = 0;
    words[3] = 0;
    words[4] = 0;
    words[5] = 0;
    words[6] = 0;
    words[7] = 0;
    words[8] = 0;
    words[9] = 0;
    words[10] = 0;
    words[11] = 0;
    words[12] = 0;
    words[13] = 0;
    words[14] = 0;
    words[15] = 0;
}
