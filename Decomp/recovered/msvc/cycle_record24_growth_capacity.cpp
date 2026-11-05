struct Record24 { unsigned char bytes[24]; };
struct Record24Vector {
    Record24* begin;
    Record24* end;
    Record24* capacity_end;
    unsigned growth_capacity(unsigned required) const;
};
unsigned Record24Vector::growth_capacity(unsigned required) const {
    unsigned capacity = capacity_end - begin;
    unsigned half = capacity / 2;
    if (0x0aaaaaaaU - half < capacity)
        capacity = 0;
    else
        capacity += half;
    return capacity < required ? required : capacity;
}
