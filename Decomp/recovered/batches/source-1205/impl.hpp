#ifndef RIFF_GC_PROTOTYPE_HPP
#define RIFF_GC_PROTOTYPE_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_FASTCALL __fastcall
#elif defined(__i386__)
#define RIFF_FASTCALL __attribute__((fastcall))
#else
#define RIFF_FASTCALL
#endif
namespace riff {
struct Object { uint8_t opaque[4]; uint8_t type, marked; };
struct Value { Object* object; int32_t tag; };
struct Local { Object* name; uint8_t opaque[8]; };
struct Prototype {
    uint8_t opaque0[8]; Value* constants; uint8_t opaque0c[4];
    Object** children; uint8_t opaque14[4]; Local* locals; Object** names;
    Object* source; int32_t nameCount, constantCount;
    uint8_t opaque2c[8]; int32_t childCount, localCount;
};
struct Global;
}
// Original internal register ABI: global in ECX and object in EDX.
extern "C" void RIFF_FASTCALL original_script_gc_mark_object(riff::Global*, riff::Object*);
extern "C" void RIFF_FASTCALL visit_prototype(riff::Global*, riff::Prototype*);
#endif
