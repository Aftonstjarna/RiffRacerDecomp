struct Record6 { unsigned char bytes[6]; };
struct Record6Buffer {
    Record6* begin;
    Record6* end;
    Record6* capacity_end;
    unsigned grow(unsigned requested);
};
unsigned Record6Buffer::grow(unsigned requested) {
    unsigned capacity = capacity_end - begin;
    if (0x2aaaaaaaU - capacity / 2 < capacity)
        capacity = 0;
    else
        capacity += capacity / 2;
    return capacity < requested ? requested : capacity;
}
