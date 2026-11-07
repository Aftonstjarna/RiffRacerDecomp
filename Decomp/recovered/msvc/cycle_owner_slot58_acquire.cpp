struct SharedObject {
    int *virtualBaseOffsets;
};
struct Owner {
    unsigned char reserved[0x58];
    SharedObject *slot;
    SharedObject **acquire(SharedObject **output);
};
SharedObject **Owner::acquire(SharedObject **output) {
    SharedObject *object = slot;
    *output = object;
    if (object) {
        unsigned offset = object->virtualBaseOffsets[1];
        unsigned *references = reinterpret_cast<unsigned *>(reinterpret_cast<unsigned char *>(object) + offset + 4);
        ++*references;
    }
    return output;
}
