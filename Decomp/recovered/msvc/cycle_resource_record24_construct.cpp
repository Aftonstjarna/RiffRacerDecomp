struct ResourceRecord24 {
    unsigned fields[6];
    ResourceRecord24();
};

ResourceRecord24::ResourceRecord24() {
    fields[0] = 0;
    fields[1] = 0;
    fields[2] = 0;
    fields[3] = ~0u;
    fields[4] = 0;
    fields[5] = 0;
}
