unsigned int __cdecl candidate_fragment(const unsigned short* text)
{
    const unsigned short* cursor = text;
    const unsigned short* afterFirst = text + 1;
    do {
    } while (*cursor++ != 0);
    return static_cast<unsigned int>(cursor - afterFirst);
}
