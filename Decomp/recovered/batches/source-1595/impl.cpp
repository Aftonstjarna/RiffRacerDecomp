#include "impl.hpp"

// Game.exe 0x5c2380: scalar arrives in ECX, result in EAX. The routine
// accesses no object or memory. The caller at 0x5c259e handles out-of-range
// results separately; this function deliberately does not truncate them.
uint32_t unicode_scalar_cp1252_map(uint32_t scalar) {
    switch (scalar) {
    case 0x20ac: return 0x80;
    case 0x201a: return 0x82;
    case 0x0192: return 0x83;
    case 0x201e: return 0x84;
    case 0x2026: return 0x85;
    case 0x2020: return 0x86;
    case 0x2021: return 0x87;
    case 0x02c6: return 0x88;
    case 0x2030: return 0x89;
    case 0x0160: return 0x8a;
    case 0x2039: return 0x8b;
    case 0x0152: return 0x8c;
    case 0x017d: return 0x8e;
    case 0x2018: return 0x91;
    case 0x2019: return 0x92;
    case 0x201c: return 0x93;
    case 0x201d: return 0x94;
    case 0x2022: return 0x95;
    case 0x2013: return 0x96;
    case 0x2014: return 0x97;
    case 0x02dc: return 0x98;
    case 0x2122: return 0x99;
    case 0x0161: return 0x9a;
    case 0x203a: return 0x9b;
    case 0x0153: return 0x9c;
    case 0x017e: return 0x9e;
    case 0x0178: return 0x9f;
    default: return scalar;
    }
}
