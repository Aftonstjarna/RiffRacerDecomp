struct NarrowStorage {
    union {
        char inline_buffer[16];
        char* heap_buffer;
    };
    unsigned length;
    unsigned capacity;

    char* storage_pointer();
};

char* NarrowStorage::storage_pointer() {
    if (capacity >= 16)
        return heap_buffer;
    return inline_buffer;
}
