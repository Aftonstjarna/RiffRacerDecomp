class ConvexInternalShape {
    unsigned char precedingFields[44];
    float collisionMargin;
public:
    void setMargin(float margin);
};

void ConvexInternalShape::setMargin(float margin)
{
    collisionMargin = margin;
}
