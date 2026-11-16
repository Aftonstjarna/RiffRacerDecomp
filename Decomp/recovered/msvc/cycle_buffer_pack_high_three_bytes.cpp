struct Buffer {
    unsigned char* data;
    unsigned reserved;
    unsigned size;
    void packHighThreeBytes();
};
void Buffer::packHighThreeBytes() {
    unsigned char* destination = data;
    unsigned char* source = data;
    while (unsigned(source - data) + 4 <= size) {
        ++source;
        destination[0] = *source++;
        destination[1] = *source++;
        destination[2] = *source++;
        destination += 3;
    }
    size = unsigned(destination - data);
}
