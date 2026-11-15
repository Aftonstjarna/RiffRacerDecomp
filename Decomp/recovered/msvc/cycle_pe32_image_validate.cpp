int __cdecl candidate_fragment(const unsigned char* image)
{
    if (*reinterpret_cast<const unsigned short*>(image) != 0x5a4d)
        return 0;
    const unsigned char* nt = image + *reinterpret_cast<const unsigned int*>(image + 0x3c);
    if (*reinterpret_cast<const unsigned int*>(nt) != 0x4550)
        return 0;
    return *reinterpret_cast<const unsigned short*>(nt + 0x18) == 0x10b;
}
