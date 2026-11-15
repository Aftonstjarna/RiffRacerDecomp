struct Matrix48 {
    float values[12];
    void initialize_basis();
};

void Matrix48::initialize_basis() {
    values[0] = 1.0f;
    values[1] = 0.0f;
    values[2] = 0.0f;
    values[3] = 0.0f;
    values[4] = 0.0f;
    values[5] = 1.0f;
    values[6] = 0.0f;
    values[7] = 0.0f;
    values[8] = 0.0f;
    values[9] = 0.0f;
    values[10] = 1.0f;
    values[11] = 0.0f;
}
