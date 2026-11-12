// The original BoxShape name accessor returns a pointer into Game.exe's static data.
class BoxShape {
public:
    const char* name() const;
};
const char* BoxShape::name() const {
    return reinterpret_cast<const char*>(0x009f996c);
}
