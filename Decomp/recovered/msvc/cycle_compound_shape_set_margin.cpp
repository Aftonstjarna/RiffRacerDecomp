// Original thiscall layout: collision margin is the float at offset 0x48.
class CompoundShape {
    unsigned char precedingFields[0x48];
    float margin;
public:
    void setMargin(float value);
};

void CompoundShape::setMargin(float value) {
    margin = value;
}
