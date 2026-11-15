struct Matrix3 {
    float storage[3][4];
    void copy_storage(const Matrix3* source);
};
void Matrix3::copy_storage(const Matrix3* source) {
    for (int row = 0; row < 3; ++row) {
        storage[row][0] = source->storage[row][0];
        storage[row][1] = source->storage[row][1];
        storage[row][2] = source->storage[row][2];
        storage[row][3] = source->storage[row][3];
    }
}
