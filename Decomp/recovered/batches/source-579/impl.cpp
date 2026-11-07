#include "impl.hpp"
namespace riff {
static void copyBits(void* destination, const void* source, unsigned count) {
    unsigned char* d=static_cast<unsigned char*>(destination);
    const unsigned char* s=static_cast<const unsigned char*>(source);
    for(unsigned i=0;i<count;++i) d[i]=s[i];
}
// Game.exe 0x4271a0..0x42727a; ECX=destination, EDX=source, EAX=destination.
// Call sites 0x427efa/0x427f10/0x427f22 and 0x43a79b consume EAX as a matrix.
// The original stack cookie is compiler instrumentation, not matrix state.
// No validation of either pointer exists. Full readable/writable extents required.
Matrix64* RIFF_FASTCALL Matrix64::fromAffine(const void* source) {
    const unsigned char* s=static_cast<const unsigned char*>(source);
    uint32_t translation[4]={0,0,0,0};
    copyBits(translation,s+36,12);
    copyBits(row[3],translation,16);
    // Snapshot the entire basis AFTER the translation write: observable with
    // overlap. Do not replace this with an upfront copy of the 48-byte input.
    uint32_t basisRows[3][4];
    for(unsigned r=0;r<3;++r) {
        for(unsigned c=0;c<3;++c)
            copyBits(&basisRows[r][c],s+12*c+4*r,4);
        basisRows[r][3]=0;
    }
    copyBits(row,basisRows,48);
    return this;
}
}
