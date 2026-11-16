void __fastcall candidate_fragment(unsigned* first, unsigned count)
{
    while (count != 0) {
        if (first != 0)
            *first = 0;
        ++first;
        --count;
    }
}
