// Dispatcher manifold pointer table begins at byte offset 20.
struct Dispatcher {
    unsigned reserved[5];
    void** manifolds;
    void* manifold(int index);
};
void* Dispatcher::manifold(int index) {
    return manifolds[index];
}
