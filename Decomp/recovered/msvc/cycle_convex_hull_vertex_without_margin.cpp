struct Vector4 { float x, y, z, w; };
struct ConvexHull {
    unsigned char header[12];
    // Scalar scale reads retain their original evaluation order.
    volatile Vector4 scaling;
    unsigned char state[72];
    const Vector4* vertices;
    void vertexWithoutMargin(int index, Vector4& output) const;
};
void ConvexHull::vertexWithoutMargin(int index, Vector4& output) const {
    // The original vertex buffer has a 16-byte stride.
    const Vector4* vertex = reinterpret_cast<const Vector4*>(
        reinterpret_cast<const unsigned char*>(vertices) + (static_cast<unsigned>(index) << 4));
    Vector4 scaled;
    scaled.x = scaling.x * vertex->x;
    scaled.y = vertex->y * scaling.y;
    scaled.z = vertex->z * scaling.z;
    scaled.w = 0;
    output = scaled;
}
