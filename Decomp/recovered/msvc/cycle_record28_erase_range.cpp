struct Record28 { unsigned words[7]; };
struct Iterator { Record28 *position; };
struct RecordVector {
    Record28 *begin, *end, *capacity;
    Iterator erase(Iterator firstIterator, Iterator lastIterator);
};
Iterator RecordVector::erase(Iterator firstIterator, Iterator lastIterator) {
    Record28 *first = firstIterator.position;
    Record28 *last = lastIterator.position;
    if (first == begin && last == end) {
        end = begin;
        return firstIterator;
    }
    if (first != last) {
        Record28 *destination = first;
        Record28 *oldEnd = end;
        while (last != oldEnd) {
            *destination = *last;
            ++last;
            ++destination;
        }
        end = destination;
    }
    return firstIterator;
}
