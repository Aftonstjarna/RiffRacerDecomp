#ifndef RIFF_SCRIPT_GC_SCAN_HPP
#define RIFF_SCRIPT_GC_SCAN_HPP
#include <stdint.h>
namespace riff {
struct GCObject { uint8_t opaque[4]; uint8_t type, marked; };
struct Value { GCObject* object; int32_t tag; };
struct LinkedValue {
    uint8_t opaque[5]; uint8_t marked; uint8_t padding[2];
    Value* value; uint8_t opaque2[4]; LinkedValue* next;
};
struct Global {
    uint8_t opaque[0x68];
    // The list sentinel is embedded here; only its address and next at +0x10 matter.
    LinkedValue sentinel;
    void scanLinkedValues();
};
// Integration dependency: original marker at 0x4f0ef0, ECX=global, EDX=object.
void markObject(Global*, GCObject*);
}
#endif
