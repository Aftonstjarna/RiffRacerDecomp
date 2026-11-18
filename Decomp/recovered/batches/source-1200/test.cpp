#include "impl.hpp"
#include <stdint.h>
// regparm(3) maps the dummy, operand and object to EAX, EDX and ECX;
// the fourth parameter stays on the caller-cleaned stack, as in the original.
extern "C" int __attribute__((regparm(3))) original_script_operand_validate(int, int32_t, const ScriptOperandContext*, int32_t);

extern "C" int test_main() {
    const int32_t operands[] = {(-2147483647-1), -1025, -513, -512, -257, -256, -255, -1, 0, 1, 2, 127, 254, 255, 256, 257, 258, 510, 511, 512, 513, 1023, 2147483647};
    const int32_t limits[] = {(-2147483647-1), -257, -1, 0, 1, 255, 256, 257, 511, 512, 2147483647};
    const int32_t types[] = {(-2147483647-1), -1, 0, 1, 2, 3, 4, 2147483647};
    const uint8_t regs[] = {0, 1, 127, 254, 255};
    ScriptOperandContext a, b;
    for (unsigned l=0; l<sizeof(limits)/sizeof(limits[0]); ++l)
      for (unsigned r=0; r<sizeof(regs)/sizeof(regs[0]); ++r)
        for (unsigned t=0; t<sizeof(types)/sizeof(types[0]); ++t)
          for (unsigned v=0; v<sizeof(operands)/sizeof(operands[0]); ++v) {
            uint8_t* ap = reinterpret_cast<uint8_t*>(&a);
            uint8_t* bp = reinterpret_cast<uint8_t*>(&b);
            for (unsigned i=0; i<sizeof(a); ++i) ap[i]=bp[i]=static_cast<uint8_t>(i*37+v+t);
            a.flagged_limit=b.flagged_limit=limits[l];
            a.register_limit=b.register_limit=regs[r];
            int actual=a.validate_operand(operands[v],types[t]);
            int expected=original_script_operand_validate(0,operands[v],&b,types[t]);
            if (actual != expected) return 1;
            for (unsigned i=0; i<sizeof(a); ++i)
              if (ap[i] != bp[i] || ap[i] != (i>=0x28 && i<0x2c ? reinterpret_cast<const uint8_t*>(&limits[l])[i-0x28] : i==0x4b ? regs[r] : static_cast<uint8_t>(i*37+v+t))) return 2;
          }
    return 0;
}
