struct Record { unsigned pair[2]; unsigned tail; };
struct Nested { unsigned char reserved[100]; Record first; Record second; };
struct Owner {
    unsigned char reserved[68];
    Nested* nested;
    bool copyPair(Record* second, Record* first);
};
bool Owner::copyPair(Record* second, Record* first) {
    if (nested) {
        *second = nested->second;
        *first = nested->first;
        return true;
    }
    return false;
}
