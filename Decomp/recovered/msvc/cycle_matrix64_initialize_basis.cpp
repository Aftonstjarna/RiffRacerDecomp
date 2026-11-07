struct Matrix64 {
    float elements[16];
    void initialize_basis();
};

void Matrix64::initialize_basis()
{
    elements[0] = 1.0f;
    elements[1] = 0.0f;
    elements[2] = 0.0f;
    elements[3] = 0.0f;
    elements[4] = 0.0f;
    elements[5] = 1.0f;
    elements[6] = 0.0f;
    elements[7] = 0.0f;
    elements[8] = 0.0f;
    elements[9] = 0.0f;
    elements[10] = 1.0f;
    elements[11] = 0.0f;
    elements[12] = 0.0f;
    elements[13] = 0.0f;
    elements[14] = 0.0f;
    elements[15] = 0.0f;
}
