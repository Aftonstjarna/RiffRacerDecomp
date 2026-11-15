struct ConvexCallback {
    unsigned int reserved;
    unsigned short group;
    unsigned short mask;
    bool accepts(const ConvexCallback* other) const;
};
bool ConvexCallback::accepts(const ConvexCallback* other) const {
    return (mask & other->group) != 0 && (group & other->mask) != 0;
}
