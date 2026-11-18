struct Matrix3 {
    volatile float elements[12];
    Matrix3();
};

Matrix3::Matrix3() {
    elements[0] = 0.0f;
    elements[1] = 0.0f;
    elements[2] = 0.0f;
    elements[3] = 0.0f;
    elements[4] = 0.0f;
    elements[5] = 0.0f;
    elements[6] = 0.0f;
    elements[7] = 0.0f;
    elements[8] = 0.0f;
    elements[9] = 0.0f;
    elements[10] = 0.0f;
    elements[11] = 0.0f;
    elements[0] = 1.0f;
    elements[1] = 0.0f;
    elements[2] = 0.0f;
    elements[3] = 0.0f;
    elements[4] = 1.0f;
    elements[5] = 0.0f;
    elements[6] = 0.0f;
    elements[7] = 0.0f;
    elements[8] = 1.0f;
    elements[9] = 0.0f;
    elements[10] = 0.0f;
    elements[11] = 0.0f;
}
