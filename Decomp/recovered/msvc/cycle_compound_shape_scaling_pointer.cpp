struct CompoundShape {
    unsigned char shapeState[0x4c];
    float localScaling[4];
    float* scalingPointer();
};

float* CompoundShape::scalingPointer() {
    return localScaling;
}
