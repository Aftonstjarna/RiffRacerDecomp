// Box shape vtable slot 0x50, VA 0x438d10. This query reads no object fields.
class BoxShape {
public:
    int vertex_count() const;
};

int BoxShape::vertex_count() const {
    return 8;
}
