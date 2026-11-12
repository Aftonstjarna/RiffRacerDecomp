struct Matrix {
    float rows[4][4];
    float* row(unsigned index);
};

float* Matrix::row(unsigned index) {
    return rows[index];
}
