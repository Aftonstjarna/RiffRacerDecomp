// Shared no-op member leaf at VA 0x4141c0; the explicit argument is discarded.
class SharedNoop {
public:
    void ignore(void* argument);
};

void SharedNoop::ignore(void*) {}
