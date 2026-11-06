struct Record48 {
    unsigned words[12];
    Record48(const Record48& source);
};
Record48::Record48(const Record48& source) {
    // Ordered stores preserve zero-before-copy behavior even when source aliases this.
    static_cast<volatile unsigned*>(words)[0] = 0;
    static_cast<volatile unsigned*>(words)[1] = 0;
    static_cast<volatile unsigned*>(words)[2] = 0;
    static_cast<volatile unsigned*>(words)[3] = 0;
    static_cast<volatile unsigned*>(words)[4] = 0;
    static_cast<volatile unsigned*>(words)[5] = 0;
    static_cast<volatile unsigned*>(words)[6] = 0;
    static_cast<volatile unsigned*>(words)[7] = 0;
    static_cast<volatile unsigned*>(words)[8] = 0;
    static_cast<volatile unsigned*>(words)[9] = 0;
    static_cast<volatile unsigned*>(words)[10] = 0;
    static_cast<volatile unsigned*>(words)[11] = 0;
    *this = source;
}
