struct Vector3;
struct Vector3Reference { const Vector3 *value; };
struct Vector3 {
    float x, y, z;
    float __vectorcall dot(Vector3Reference other) const;
};
float __vectorcall Vector3::dot(Vector3Reference other) const {
    return y * other.value->y + x * other.value->x + z * other.value->z;
}
