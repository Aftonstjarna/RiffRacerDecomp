struct U32Vector {
    unsigned* begin;
    unsigned* end;
    unsigned* limit;
    unsigned growth_capacity(unsigned requested) const;
};

unsigned U32Vector::growth_capacity(unsigned requested) const {
    unsigned capacity = limit - begin;
    unsigned half = capacity / 2;
    if (0x3fffffffU - half < capacity)
        capacity = 0;
    else
        capacity += half;
    return capacity < requested ? requested : capacity;
}
