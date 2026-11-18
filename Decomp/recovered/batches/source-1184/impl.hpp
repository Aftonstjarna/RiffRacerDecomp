#ifndef RIFF_GC_BEGIN_MARK_HPP
#define RIFF_GC_BEGIN_MARK_HPP
#include <stdint.h>
namespace riff {
struct Object { uint8_t unknown[4]; uint8_t type, marks; };
struct Value { Object* object; int32_t tag; };
struct ThreadObject {
    uint8_t unknown[0x48]; Value value;
};
struct Global {
    uint8_t unknown0[0x15]; uint8_t phase;
    uint8_t unknown1[0x0e]; Object* gray; Object* gray_again; Object* weak;
    uint8_t unknown2[0x2c]; Value value; ThreadObject* main_thread;
    uint8_t unknown3[0x14]; Object* roots[9];
};
struct State {
    uint8_t unknown[0x10]; Global* global;
    void beginMark();
};
// Integration dependencies at 0x4f0ef0 and 0x4f1fe0 respectively.
void markObject(Global*, Object*);
void scanRoots(Global*);
}
#endif
