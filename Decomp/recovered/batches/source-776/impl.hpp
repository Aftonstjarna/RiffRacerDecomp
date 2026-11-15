#ifndef RIFF_SCRIPT_TABLE_HPP
#define RIFF_SCRIPT_TABLE_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_FASTCALL __attribute__((fastcall))
#endif
namespace riff {
// Only observed fields are named. String bytes and interning are outside scope.
struct ScriptString { uint8_t unknown[8]; uint32_t hash; };
struct ScriptNode {
    uint32_t valueBits;
    uint32_t valueType;
    const ScriptString* key;
    uint32_t keyType;
    ScriptNode* next;
};
struct ScriptTable {
    uint8_t unknown0[7];
    uint8_t logNodeCount;
    uint8_t unknown8[8];
    ScriptNode* nodes;
    ScriptNode* RIFF_FASTCALL getString(const ScriptString* key) const;
};
static_assert(sizeof(void*) == 4, "Original layouts require 32-bit pointers");
static_assert(sizeof(ScriptNode) == 20, "Original node stride");
static_assert(offsetof(ScriptTable, nodes) == 16, "Original node array field");
}
#endif
