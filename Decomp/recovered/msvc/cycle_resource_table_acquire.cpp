struct Resource {
    unsigned tag;
    unsigned references;
};
struct ResourceHandle {
    Resource *resource;
};
struct ResourceTable {
    Resource **entries;
    ResourceHandle acquire(unsigned index);
};
ResourceHandle ResourceTable::acquire(unsigned index) {
    ResourceHandle result;
    result.resource = entries[index];
    if (result.resource)
        ++result.resource->references;
    return result;
}
