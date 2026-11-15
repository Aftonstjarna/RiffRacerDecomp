struct Vector4 { float x, y, z, w; };
struct Sphere {
    Vector4* supportWithoutMargin(Vector4* result, const Vector4* direction) const;
};
Vector4* Sphere::supportWithoutMargin(Vector4* result, const Vector4*) const {
    result->x = 0.0f;
    result->y = 0.0f;
    result->z = 0.0f;
    result->w = 0.0f;
    return result;
}
