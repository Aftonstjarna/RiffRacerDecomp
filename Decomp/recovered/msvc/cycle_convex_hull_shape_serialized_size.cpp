// Original VA 0x47cd30: serialization records for btConvexHullShape occupy 68 bytes.
// This virtual-method body does not inspect the object or change any fields.
class btConvexHullShape {
public:
    int calculateSerializeBufferSize() const;
};

int btConvexHullShape::calculateSerializeBufferSize() const
{
    return 68;
}
