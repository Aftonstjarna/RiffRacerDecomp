// Simplex query result storage. Only the low four status bits are reset.
struct SimplexResult {
    unsigned char preserved[16];
    unsigned short status;
    unsigned short reserved;
    unsigned weights[4];
    unsigned char valid;
    void reset();
};
void SimplexResult::reset() {
    valid = 0;
    weights[0] = 0;
    weights[1] = 0;
    weights[2] = 0;
    weights[3] = 0;
    status &= 0xfff0;
}
