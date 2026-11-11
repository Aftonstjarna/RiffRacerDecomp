#include "impl.hpp"
namespace riff {
// Game.exe VA 0x439220, RVA 0x39220, 103 bytes; ECX=this, EAX=this,
// no stack arguments, plain ret. No allocation, release, SEH or global access.
// Direct callers include 0x439d7b (object+4), 0x4693ce (object+0x14c),
// 0x4693d9 (object+0x19c), and 0x482627 (object+0x38).
// A neighboring cleanup at 0x439290 tests +0x48 and +0x4c before release;
// this initializer itself never examines or releases prior field contents.
FourRecord20* RIFF_THISCALL FourRecord20::initialize() {
    for (unsigned i = 0; i != 4; ++i) {
        records[i].flag10 = 1;
        records[i].field0c = 0;
        records[i].field04 = 0;
        records[i].field08 = 0;
    }
    return this;
}
}
