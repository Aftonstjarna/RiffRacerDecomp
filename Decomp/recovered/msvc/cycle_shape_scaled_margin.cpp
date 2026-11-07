class Shape {
    unsigned reserved0[3];
    float scale;
    unsigned reserved1[3];
    float margin;
public:
    float scaledMargin() const;
};

float Shape::scaledMargin() const {
    return margin * scale;
}
