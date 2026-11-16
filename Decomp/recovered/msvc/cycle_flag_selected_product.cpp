struct ProductState {
    unsigned char reserved[0x6cec];
    unsigned flags;
    unsigned ordinaryFactor;
    unsigned baseFactor;
    unsigned __fastcall selectedProduct(unsigned multiplier);
};
unsigned __fastcall ProductState::selectedProduct(unsigned multiplier) {
    if (flags & 0x4000)
        return (baseFactor * multiplier) << 2;
    return baseFactor * ordinaryFactor * multiplier;
}
