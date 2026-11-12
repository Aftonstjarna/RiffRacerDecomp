// Box shape vtable slot +0x54, original VA 0x438D20.
// Every box has twelve edges. This query reads no object fields.
class BoxShape {
public:
    int edgeCount() const;
};

int BoxShape::edgeCount() const {
    return 12;
}
