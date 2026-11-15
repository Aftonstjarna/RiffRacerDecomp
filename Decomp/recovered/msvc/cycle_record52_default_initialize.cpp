struct Record52 {
    float value;
    unsigned reserved[6];
    int index;
    unsigned flags;
    float scale[4];
    Record52* initialize();
};
Record52* Record52::initialize() {
    value = -1.0f;
    reserved[0] = 0;
    reserved[1] = 0;
    reserved[2] = 0;
    reserved[3] = 0;
    reserved[4] = 0;
    reserved[5] = 0;
    index = -1;
    flags = 0;
    scale[0] = 1.0f;
    scale[1] = 1.0f;
    scale[2] = 1.0f;
    scale[3] = 1.0f;
    return this;
}
