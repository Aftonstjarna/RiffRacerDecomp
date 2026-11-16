class CompoundShape {
    unsigned char precedingFields[0x48];
    float margin;
public:
    float getMargin() const;
};

float CompoundShape::getMargin() const {
    return margin;
}
