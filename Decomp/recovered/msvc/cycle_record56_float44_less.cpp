// Compares the float at byte offset 44 in two 56-byte records.
struct Record56 {
    unsigned char prefix[44];
    float value;
    unsigned char suffix[8];
};
int __cdecl candidate_fragment(const Record56* left, const Record56* right) {
    return right->value > left->value;
}
