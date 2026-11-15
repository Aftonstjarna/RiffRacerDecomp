struct Object {
    unsigned char reserved[0x78];
    unsigned field78;
    int field78_present() const;
};

int Object::field78_present() const {
    return field78 != 0;
}
