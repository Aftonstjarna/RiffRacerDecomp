// Original VA 0x434320: ordered assignment of a forty-byte record.
struct Record40 {
    unsigned a, b, c, d, e, f, g, h, i, j;
    Record40& operator=(const Record40& source);
};

Record40& Record40::operator=(const Record40& source) {
    a = source.a;
    b = source.b;
    c = source.c;
    d = source.d;
    e = source.e;
    f = source.f;
    g = source.g;
    h = source.h;
    i = source.i;
    j = source.j;
    return *this;
}
