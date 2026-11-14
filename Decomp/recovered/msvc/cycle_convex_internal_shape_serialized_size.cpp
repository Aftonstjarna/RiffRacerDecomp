class ConvexInternalShape {
public:
    int calculateSerializeBufferSize() const;
};

int ConvexInternalShape::calculateSerializeBufferSize() const {
    return 52;
}
