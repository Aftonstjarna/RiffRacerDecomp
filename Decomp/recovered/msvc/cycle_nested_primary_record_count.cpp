struct PrimaryRecords {
    unsigned reserved[2];
    unsigned count;
};

struct RecordOwner {
    unsigned reserved[8];
    PrimaryRecords* primary;
    unsigned record_count() const;
};

unsigned RecordOwner::record_count() const {
    if (primary)
        return primary->count;
    return 0;
}
