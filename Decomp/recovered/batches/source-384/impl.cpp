#include "impl.hpp"
namespace {
// Copy representation, avoiding floating-point loads/conversions (including
// signaling-NaN quieting). Snapshot each word before writing, as in the original.
void copy_word(float& destination, const float& source) {
    unsigned char word[4];
    const unsigned char* input = reinterpret_cast<const unsigned char*>(&source);
    for (unsigned i = 0; i != 4; ++i) word[i] = input[i];
    unsigned char* output = reinterpret_cast<unsigned char*>(&destination);
    for (unsigned i = 0; i != 4; ++i) output[i] = word[i];
}
}
Vector3* RIFF_THISCALL Vector3::construct_refs(const float& a, const float& b, const float& c) {
    // Do not prefetch all inputs: b/c can refer to fields changed by earlier stores.
    copy_word(x, a);
    copy_word(y, b);
    copy_word(z, c);
    fourth = 0.0f;
    return this;
}
// Evidence: direct original disassembly agrees with the accepted reference.
// Callers at 0x465990/0x4659cb pass three float-local addresses and stack-vector
// destinations; adjacent code uses four-byte component indexing. No imports,
// allocation, arithmetic, FS registration or global side effects occur here.
