#include "impl.hpp"
namespace riff {
// Evidence: original instructions and caller at 0x542230. That caller pushes
// names and table fields +0x10/+0x14 and stores handles at +0x18 onward.
// Slots +0x14/+0x18/+0x20 have explicit stack self pointers, COM stdcall ABI.
// Only exact zero from getDescription permits enumeration (not HRESULT >= 0).
// Descriptor name is read even on a nonzero parameter-description status.
// Neither descriptions nor count outputs are initialized beyond count=1;
// callbacks must supply valid data. No ownership/refcount operation occurs.

ParameterHandle RIFF_STDCALL shaderParameterLookup(ConstantTable* table, const char* name) {
    if (!table) return 0;
    TableDescription description;
    if (table->vtable->getDescription(table, &description) != 0) return 0;
    for (uint32_t index = 0; index < description.constants; ++index) {
        uint32_t count = 1;
        ParameterHandle handle = table->vtable->getConstant(table, 0, index);
        if (!handle) continue;
        ParameterDescription parameter;
        // Deliberately ignore status and output count, as the original does.
        table->vtable->getParameterDescription(table, handle, &parameter, &count);
        const char* candidate = parameter.name;
        const char* requested = name;
        while (*candidate == *requested) {
            if (*candidate == '\0') return handle;
            ++candidate;
            ++requested;
        }
    }
    return 0;
}
}
