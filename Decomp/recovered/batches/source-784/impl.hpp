#ifndef RIFF_SCRIPT_TABLE_LENGTH_HPP
#define RIFF_SCRIPT_TABLE_LENGTH_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#define RIFF_FASTCALL __fastcall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#define RIFF_FASTCALL __attribute__((fastcall))
#endif
struct ScriptValue { uint32_t payload; uint32_t tag; };
struct ScriptTable {
    uint8_t unknown00[12];
    ScriptValue* array;             // +0x0c, one-based logical indexing
    void* hash;                     // +0x10; empty sentinel is VA 0x99a424
    uint8_t unknown14[8];
    uint32_t arraySize;             // +0x1c
    uint32_t RIFF_THISCALL length() const;
};
// Original helper at 0x4f0d80 takes table in ECX and lower bound in EDX.
// Integration supplies this dependency; it is outside the recovered scope.
extern "C" uint32_t RIFF_FASTCALL script_table_hash_boundary(const ScriptTable*, uint32_t);
#endif
