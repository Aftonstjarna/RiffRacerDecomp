struct Vector4 { float x, y, z, w; };
class Sphere {
public:
    void batchedSupportWithoutMargin(const Vector4* directions, Vector4* support, int count) const;
};
void Sphere::batchedSupportWithoutMargin(const Vector4*, Vector4* support, int count) const {
    for (int i = 0; i < count; ++i) {
        support[i].x = 0;
        support[i].y = 0;
        support[i].z = 0;
        support[i].w = 0;
    }
}
