struct NarrowString {
    union { char inline_storage[16]; char* heap_storage; } storage;
    unsigned length;
    unsigned capacity;
    char** end_pointer(char** result);
};

char** NarrowString::end_pointer(char** result) {
    char* first;
    if (capacity >= 16)
        first = storage.heap_storage;
    else
        first = storage.inline_storage;
    *result = first + length;
    return result;
}
