#ifndef RIFF_HASH_BOUNDARY_HPP
#define RIFF_HASH_BOUNDARY_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_FASTCALL __attribute__((fastcall))
#endif
struct ScriptValue { uint32_t payload, tag; };
struct ScriptNode { ScriptValue value; float key; uint32_t keyTag; ScriptNode* next; };
struct ScriptTable {
    uint8_t unknown00[7];
    uint8_t hashLogSize; // +7; x86 masks shift count to five bits
    uint8_t unknown08[4];
    ScriptValue* array; // +0xc
    ScriptNode* hash;   // +0x10, nodes have stride 20
    uint8_t unknown14[8];
    uint32_t arraySize; // +0x1c
    uint32_t RIFF_FASTCALL hashBoundary(uint32_t lower) const;
};
// Accepted dependency at 0x4f0ae0: ECX table, EDX integer, EAX value pointer.
extern "C" const ScriptValue* RIFF_FASTCALL script_table_get_integer(const ScriptTable*, uint32_t);
#endif
