// The scaling vector begins twelve bytes into the original object.
class ConvexInternalShape {
    unsigned char shapeHeader[12];
    float localScaling[4];
public:
    float* scalingPointer();
};

float* ConvexInternalShape::scalingPointer() {
    return localScaling;
}
