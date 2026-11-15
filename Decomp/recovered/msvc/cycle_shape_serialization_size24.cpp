// Original VA 0x415c10. Serialized record size is independent of object state.
class Shape {
public:
    int serializedSize() const;
};

int Shape::serializedSize() const {
    return 24;
}
