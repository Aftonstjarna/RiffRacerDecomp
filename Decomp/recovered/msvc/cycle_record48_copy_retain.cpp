struct Retained { unsigned tag; unsigned references; };
struct Record48 {
    Retained* first;
    Retained* second;
    Retained* third;
    Retained* fourth;
    unsigned a, b, c, d, e, f, g, h;
    Record48* copyRetain(const Record48* source);
};
Record48* Record48::copyRetain(const Record48* source) {
    first = source->first;
    if (first) ++first->references;
    second = source->second;
    if (second) ++second->references;
    third = source->third;
    if (third) ++third->references;
    fourth = source->fourth;
    if (fourth) ++fourth->references;
    a = source->a;
    b = source->b;
    c = source->c;
    d = source->d;
    e = source->e;
    f = source->f;
    g = source->g;
    h = source->h;
    return this;
}
