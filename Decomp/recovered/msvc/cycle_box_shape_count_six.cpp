// Shared box-shape count leaf at Game.exe VA 0x438d00.
// The object is not accessed by this method.
class BoxShape {
public:
    int count() const;
};

int BoxShape::count() const {
    return 6;
}
