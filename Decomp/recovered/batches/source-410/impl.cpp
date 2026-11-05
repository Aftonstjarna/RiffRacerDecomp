#include "impl.hpp"

// Original ABI: ECX=this, no stack arguments, EAX=this, plain RET.
// A genuine constructor preserves the native MSVC thiscall constructor ABI.
// The caller at 0x528475 allocates 0x234 bytes, checks for allocation failure,
// and stores this constructor's result at 0xbfbaac. Null is not valid here.
WorkerState::WorkerState() {
    // Keep the original pairwise traversal and store order. Every byte is set;
    // there is no allocation, imported call, floating arithmetic or FS access.
    for (unsigned pair = 0; pair < 12; ++pair) {
        const unsigned i = pair * 2;
        values[i] = 0.6f;
        zeroWordsA[i] = 0;
        zeroWordsB[i] = 0;
        stateWords[i] = 2;
        flagBytes[pair * 3] = 0;
        records[pair].words[0] = 0;
        values[i + 1] = 0.6f;
        zeroWordsA[i + 1] = 0;
        zeroWordsB[i + 1] = 0;
        stateWords[i + 1] = 2;
        flagBytes[pair * 3 + 1] = 0;
        records[pair].words[1] = 0;
        flagBytes[pair * 3 + 2] = 0;
        records[pair].words[2] = 0;
    }
}
