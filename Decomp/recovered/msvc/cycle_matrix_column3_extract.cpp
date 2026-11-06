struct Vector3 {
    float x, y, z, w;
};
struct Matrix {
    float elements[16];
    Vector3 column3(unsigned column) const;
};
Vector3 Matrix::column3(unsigned column) const {
    Vector3 result;
    result.w = 0;
    result.x = elements[column];
    result.y = elements[column + 4];
    result.z = elements[column + 8];
    return result;
}
