#include "impl.hpp"

// Game.exe 0x426f30..0x426f95 (RVA 0x26f30). ECX=this, nine
// pointer arguments, callee pops 36 bytes, EAX=this. No helper calls.
// Represent the constructor as a member returning this so the original return
// contract is observable. Do not stage the inputs: aliases observe earlier
// writes. In particular d and g are read AFTER the preceding padding is zeroed.
// The direct call at 0x4d8ca6 constructs global 0xc0d508 from nine
// stack references containing zero. Source type/row-vs-column names are not
// recoverable from this integer-only copy routine; words are opaque bit values.
Matrix3* RIFF_THISCALL Matrix3::construct_refs(
    const uint32_t& a, const uint32_t& b, const uint32_t& c,
    const uint32_t& d, const uint32_t& e, const uint32_t& f,
    const uint32_t& g, const uint32_t& h, const uint32_t& i) {
    words[0] = a;
    words[1] = b;
    words[2] = c;
    words[3] = 0;
    words[4] = d;
    words[5] = e;
    words[6] = f;
    words[7] = 0;
    words[8] = g;
    words[9] = h;
    words[10] = i;
    words[11] = 0;
    return this;
}
