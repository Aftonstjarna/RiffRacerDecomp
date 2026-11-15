#include "impl.hpp"
#ifdef _MSC_VER
#include <emmintrin.h>
#endif
namespace riff {
// Original range [0x4f0bb0,0x4f0c36). Data dispatch at 0x4f0c38:
// tag 0 -> found, 1/2 -> payload identity, 3 -> ordered float equality.
// Callers at 0x487214 and 0x48755f copy the returned eight-byte Value.
// This lookup does not write table flags (the callers sometimes do).
const Value* RIFF_FASTCALL Table::getValue(const Value* key) const {
    const Value* nil=reinterpret_cast<const Value*>(uintptr_t(0x99a41c));
    const uint32_t tag=key->tag;
    if(tag==0) return nil;
    if(tag==4) return getString(key->payload.string);
    if(tag==3) {
        // SSE conversion is intentional: out-of-range/NaN produces INT_MIN,
        // then the ordered comparison decides whether the integer path applies.
        // Avoid undefined C++ float-to-int conversions. Preserve MXCSR effects.
#ifdef _MSC_VER
        int32_t integer=_mm_cvttss_si32(_mm_load_ss(&key->payload.number));
        float rounded=_mm_cvtss_f32(_mm_cvtepi32_ps(_mm_cvtsi32_si128(integer)));
#else
        typedef float Float4 __attribute__((vector_size(16)));
        typedef int Int4 __attribute__((vector_size(16)));
        Float4 number={key->payload.number,0,0,0};
        int32_t integer=__builtin_ia32_cvttss2si(number);
        Int4 lanes={integer,0,0,0};
        float rounded=__builtin_ia32_cvtdq2ps(lanes)[0];
#endif
        if(rounded==key->payload.number) return getInteger(integer);
    }
    Node* node=mainBucket(key);
    do {
        if(node->key.tag==tag) {
            if(tag==3) {
                if(node->key.payload.number==key->payload.number)
                    return &node->value;
            } else if(node->key.payload.bits==key->payload.bits) {
                return &node->value;
            }
        }
        node=node->next;
    } while(node);
    return nil;
}
}
