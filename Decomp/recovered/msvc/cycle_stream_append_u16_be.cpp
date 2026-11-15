struct Stream {
    unsigned reserved0[2];
    unsigned char* buffer;
    unsigned reserved1[2];
    unsigned position;
    void __fastcall append(unsigned value);
};
void __fastcall Stream::append(unsigned value) {
    buffer[position] = static_cast<unsigned char>(value >> 8);
    ++position;
    buffer[position] = static_cast<unsigned char>(value);
    ++position;
}
