// A 64-byte matrix with unaligned storage; assignment returns the destination.
struct Matrix64 {
    struct Storage { float values[16]; } storage;
    Matrix64& operator=(const Matrix64& source);
};

Matrix64& Matrix64::operator=(const Matrix64& source) {
    storage = source.storage;
    return *this;
}
