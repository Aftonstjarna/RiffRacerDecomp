struct Dispatcher {
    unsigned char reserved[20];
    void** manifolds;
    void** manifoldArray();
};

void** Dispatcher::manifoldArray() {
    return manifolds;
}
