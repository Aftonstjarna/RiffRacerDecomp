// Original thiscall leaf at 0x438850. The margin occupies offset 0x2c.
class ConvexInternalShape {
    unsigned char precedingFields[44];
    float margin;
public:
    float getMargin() const;
};

float ConvexInternalShape::getMargin() const {
    return margin;
}
