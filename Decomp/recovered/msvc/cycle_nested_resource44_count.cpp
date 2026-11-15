struct Resource {
    unsigned char reserved[0x1c];
    unsigned count;
};
struct Owner {
    unsigned char reserved[0x44];
    Resource* resource;
    unsigned count() const;
};
unsigned Owner::count() const {
    if (resource)
        return resource->count;
    return 0;
}
