#ifndef RIFF_SHADER_PARAMETER_LOOKUP_HPP
#define RIFF_SHADER_PARAMETER_LOOKUP_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_STDCALL __stdcall
#elif defined(__i386__)
#define RIFF_STDCALL __attribute__((stdcall))
#else
#define RIFF_STDCALL
#endif
namespace riff {
typedef const char* ParameterHandle;
struct TableDescription {
    const char* creator;
    uint32_t version;
    uint32_t constants;
};
struct ParameterDescription {
    const char* name;
    uint32_t registerSet, registerIndex, registerCount;
    uint32_t parameterClass, parameterType;
    uint32_t rows, columns, elements, structMembers, bytes;
    const void* defaultValue;
};
struct ConstantTable;
// COM entries 0..4 are unused here (IUnknown and buffer accessors).
struct ConstantTableVtable {
    void (RIFF_STDCALL *unused[5])();
    int32_t (RIFF_STDCALL *getDescription)(ConstantTable*, TableDescription*);
    int32_t (RIFF_STDCALL *getParameterDescription)(ConstantTable*, ParameterHandle,
                                                   ParameterDescription*, uint32_t*);
    void (RIFF_STDCALL *unused7)();
    ParameterHandle (RIFF_STDCALL *getConstant)(ConstantTable*, ParameterHandle, uint32_t);
};
struct ConstantTable { const ConstantTableVtable* vtable; };
// Original 0x542340..0x5423d5: stack arguments table/name, ret 8; no this pointer.
ParameterHandle RIFF_STDCALL shaderParameterLookup(ConstantTable* table, const char* name);
}
#endif
