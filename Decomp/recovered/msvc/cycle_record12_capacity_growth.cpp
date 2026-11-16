struct Record12 { unsigned words[3]; };
struct RecordVector {
    Record12 *begin;
    Record12 *end;
    Record12 *capacity_end;
    unsigned grow(unsigned minimum);
};
unsigned RecordVector::grow(unsigned minimum) {
    unsigned capacity = capacity_end - begin;
    unsigned growth = capacity / 2;
    if (0x15555555u - growth < capacity)
        capacity = 0;
    else
        capacity += growth;
    return capacity < minimum ? minimum : capacity;
}
