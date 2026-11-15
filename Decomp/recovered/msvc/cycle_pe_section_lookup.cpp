void* __cdecl candidate_fragment(unsigned char* image, unsigned int address)
{
    unsigned char* header = image + *reinterpret_cast<unsigned int*>(image + 0x3c);
    unsigned int index = 0;
    unsigned int count = *reinterpret_cast<unsigned short*>(header + 6);
    unsigned char* section = header + 24 + *reinterpret_cast<unsigned short*>(header + 20);
    for (; index < count; ++index, section += 40) {
        unsigned int start = *reinterpret_cast<unsigned int*>(section + 12);
        if (address >= start && address < start + *reinterpret_cast<unsigned int*>(section + 8))
            return section;
    }
    return 0;
}
