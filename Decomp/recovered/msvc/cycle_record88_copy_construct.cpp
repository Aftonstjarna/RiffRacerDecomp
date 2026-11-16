// Original ABI: 88-byte record, 22 consecutive 32-bit fields.
struct Record88 {
    unsigned word0, word1, word2, word3, word4, word5, word6, word7, word8, word9, word10, word11, word12, word13, word14, word15, word16, word17, word18, word19, word20, word21;
    Record88(const Record88& source);
};

Record88::Record88(const Record88& source)
{
    word0 = source.word0;
    word1 = source.word1;
    word2 = source.word2;
    word3 = source.word3;
    word4 = source.word4;
    word5 = source.word5;
    word6 = source.word6;
    word7 = source.word7;
    word8 = source.word8;
    word9 = source.word9;
    word10 = source.word10;
    word11 = source.word11;
    word12 = source.word12;
    word13 = source.word13;
    word14 = source.word14;
    word15 = source.word15;
    word16 = source.word16;
    word17 = source.word17;
    word18 = source.word18;
    word19 = source.word19;
    word20 = source.word20;
    word21 = source.word21;
}
