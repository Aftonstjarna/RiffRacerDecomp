struct Record12 {
    unsigned first;
    unsigned sentinel;
    unsigned last;
};
void __fastcall candidate_fragment(Record12* records, unsigned count) {
    while (count) {
        if (records) {
            records->first = 0;
            records->sentinel = ~0u;
            records->last = 0;
        }
        records = records + 1;
        --count;
    }
}
