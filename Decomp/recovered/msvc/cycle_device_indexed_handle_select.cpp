struct Device {
    unsigned char reserved[3];
    unsigned char usePrimary;
    unsigned primary[263];
    unsigned alternate[11];
    unsigned selectedIndex;
    unsigned selectHandle();
};

unsigned Device::selectHandle()
{
    if (usePrimary)
        return primary[selectedIndex];
    return alternate[selectedIndex];
}
