struct ResourceIndex {
    unsigned reserved[13];
    unsigned* begin;
    unsigned* end;
    unsigned capacity;
    unsigned* references;
    unsigned acquire(unsigned index);
};
unsigned ResourceIndex::acquire(unsigned index) {
    if (index >= static_cast<unsigned>(end - begin))
        return 0;
    ++references[index];
    return begin[index];
}
