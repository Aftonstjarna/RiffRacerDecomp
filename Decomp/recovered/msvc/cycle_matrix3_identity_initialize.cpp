struct Matrix3 {
    float entries[12];
    void initializeIdentity();
};

void Matrix3::initializeIdentity()
{
    entries[0] = 1.0f;
    entries[1] = 0.0f;
    entries[2] = 0.0f;
    entries[3] = 0.0f;
    entries[4] = 1.0f;
    entries[5] = 0.0f;
    entries[6] = 0.0f;
    entries[7] = 0.0f;
    entries[8] = 1.0f;
    entries[9] = 0.0f;
    entries[10] = 0.0f;
    entries[11] = 0.0f;
}
