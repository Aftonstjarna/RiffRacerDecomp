#ifndef RIFF_COMMON_PARAMETERS_HPP
#define RIFF_COMMON_PARAMETERS_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define RIFF_STDCALL __stdcall
#define RIFF_THISCALL __thiscall
#else
#define RIFF_STDCALL __attribute__((stdcall))
#define RIFF_THISCALL __attribute__((thiscall))
#endif
namespace riff {
struct ConstantTable;
typedef const char* ParameterHandle;
// Reference helper 0x542340, not part of this recovery. Port supplies this
// stdcall dependency (exact, case-sensitive top-level constant lookup).
ParameterHandle RIFF_STDCALL lookupParameter(ConstantTable*, const char*);
struct Shader {
    uint32_t unknown00[4];
    ConstantTable* vertexConstants; // +10
    ConstantTable* pixelConstants;  // +14
    ParameterHandle vertexReposition, pixelReposition; // +18,+1c
    ParameterHandle fogParams, fogColour, fogHeightParams; // +20..28
    ParameterHandle shadowMapPos; // +2c (assigned after +44)
    ParameterHandle alphaValue, specularScale, specularPower; // +30..38
    ParameterHandle ambientColor, diffuseColor, specularColor; // +3c..44
    ParameterHandle maskColor, shadowColor, skinMatrixArray, morphAmounts; // +48..54
    void RIFF_THISCALL bindCommonParameters();
};
}
#endif
