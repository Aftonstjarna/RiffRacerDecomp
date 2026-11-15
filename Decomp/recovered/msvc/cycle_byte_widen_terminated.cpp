void candidate_fragment(unsigned short* destination, const volatile unsigned char* source, unsigned size_bytes)
{
    unsigned remaining = size_bytes >> 1;
    while (*source) {
        if (remaining <= 1)
            break;
        --remaining;
        *destination++ = *source++;
    }
    *destination = 0;
}
