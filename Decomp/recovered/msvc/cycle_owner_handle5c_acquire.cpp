struct Handle {
    int* offsets;
};
struct Owner {
    unsigned char reserved[0x5c];
    Handle* handle;
    Handle** acquire(Handle** output);
};
Handle** Owner::acquire(Handle** output) {
    Handle* value = handle;
    *output = value;
    if (value) {
        unsigned* references = reinterpret_cast<unsigned*>(
            reinterpret_cast<unsigned char*>(value) + value->offsets[1] + 4);
        ++*references;
    }
    return output;
}
