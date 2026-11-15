struct Record68 {
    unsigned a,b,c,d,e,f,g,h,i,j,k,l,m;
    struct Tail { unsigned words[4]; } tail;
    Record68(const Record68& other);
};
Record68::Record68(const Record68& other)
    : a(other.a), b(other.b), c(other.c), d(other.d), e(other.e),
      f(other.f), g(other.g), h(other.h), i(other.i), j(other.j),
      k(other.k), l(other.l), m(other.m), tail(other.tail) {}
