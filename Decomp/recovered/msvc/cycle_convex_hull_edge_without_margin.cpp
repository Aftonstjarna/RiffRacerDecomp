// Original Game.exe: VA 0x47d1d0, 171 bytes; x86 thiscall.
struct Vector { float x, y, z, w; };
struct ConvexHull {
    unsigned char prefix[12];
    // Preserve the original individual scale reads, including output aliasing.
    volatile Vector scaling;
    unsigned char middle[64]; // Vertex count at 0x5c; point data pointer at 0x64.
    int count;
    int capacity;
    Vector* points;
    void edge(int index, Vector& first, Vector& second) const;
};
void ConvexHull::edge(int index, Vector& first, Vector& second) const {
    const int vertexCount = count;
    const Vector& a = points[index % vertexCount];
    Vector scaled;
    scaled.w = 0.0f;
    scaled.x = a.x * scaling.x;
    scaled.y = a.y * scaling.y;
    scaled.z = a.z * scaling.z;
    first = scaled;
    const Vector& b = points[(index + 1) % vertexCount];
    scaled.w = 0.0f;
    scaled.x = b.x * scaling.x;
    scaled.y = b.y * scaling.y;
    scaled.z = b.z * scaling.z;
    second = scaled;
}
