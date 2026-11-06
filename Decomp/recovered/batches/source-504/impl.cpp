#include "impl.hpp"
namespace {
// Snapshot each transfer before writing: memcpy of the entire record would
// lose the original behavior when the first eight bytes overwrite its tail.
template<unsigned N> void transfer(unsigned char* dst, const unsigned char* src) {
    unsigned char value[N];
    unsigned i;
    for (i = 0; i < N; ++i) value[i] = src[i];
    for (i = 0; i < N; ++i) dst[i] = value[i];
}
}
// Game.exe 0x490e70..0x490eaf: thiscall, two stack args, bool in AL.
// Observed direct caller 0x5156f3 supplies stack records and consumes first
// record as three floats. Keep their bits opaque; no arithmetic occurs here.
bool RIFF_THISCALL PairCopyOwner::copyRecordPair(void* first, void* second) {
    unsigned char* source = nested;
    if (!source) return false;
    unsigned char* out = static_cast<unsigned char*>(first);
    transfer<8>(out, source + 0x70);
    transfer<4>(out + 8, source + 0x78);
    source = nested; // first output can even replace this pointer
    out = static_cast<unsigned char*>(second);
    transfer<8>(out, source + 0x64);
    transfer<4>(out + 8, source + 0x6c);
    return true;
}
