struct NestedRecord {
    unsigned reserved[5];
    unsigned count;
};

struct RecordOwner {
    unsigned reserved[17];
    NestedRecord* nested;
    unsigned count() const;
};

unsigned RecordOwner::count() const {
    if (nested)
        return nested->count;
    return 0;
}
