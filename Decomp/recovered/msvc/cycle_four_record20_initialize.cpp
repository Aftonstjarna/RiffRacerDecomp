struct Record20 {
    unsigned untouched;
    unsigned first;
    unsigned second;
    unsigned third;
    unsigned char enabled;
    unsigned char padding[3];
};
struct FourRecords {
    Record20 records[4];
    FourRecords* initialize();
};
FourRecords* FourRecords::initialize() {
    records[0].enabled = 1;
    records[0].third = 0;
    records[0].first = 0;
    records[0].second = 0;
    records[1].enabled = 1;
    records[1].third = 0;
    records[1].first = 0;
    records[1].second = 0;
    records[2].enabled = 1;
    records[2].third = 0;
    records[2].first = 0;
    records[2].second = 0;
    records[3].enabled = 1;
    records[3].third = 0;
    records[3].first = 0;
    records[3].second = 0;
    return this;
}
