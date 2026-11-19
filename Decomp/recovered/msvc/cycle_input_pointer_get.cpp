struct Point { int x, y; };
struct Input {
    unsigned char reserved[0x23c];
    int x, y;
    unsigned char reserved2[2];
    unsigned char disabled;
    Point *get(Point *out);
};
Point *Input::get(Point *out) {
    if (disabled) {
        out->x = 0;
        out->y = 0;
    } else {
        out->x = x;
        out->y = y;
    }
    return out;
}
