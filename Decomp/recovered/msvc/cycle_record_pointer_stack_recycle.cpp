struct RecordPointerStack {
    unsigned entries[8];
    unsigned count;
};
struct RecordPool {
    unsigned reserved[86];
    unsigned recycled[4];
    unsigned count;
    void recycle(RecordPointerStack* source);
};
void RecordPool::recycle(RecordPointerStack* source) {
    --source->count;
    recycled[count] = source->entries[source->count];
    ++count;
}
