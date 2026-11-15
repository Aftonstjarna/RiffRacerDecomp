struct ConvexHull {
    unsigned char preceding_fields[92];
    unsigned int vertex_edge_count;
    unsigned int count() const;
};

unsigned int ConvexHull::count() const {
    return vertex_edge_count;
}
