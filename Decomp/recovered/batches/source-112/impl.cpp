#include "impl.hpp"
namespace riff {
// Original 0x542230..0x542335: ECX=this, no stack arguments, RET.
// Caller 0x5676ce restores ECX to the constructed shader before calling.
// No ownership operations, error branch, or initialization of unrelated fields.
// Every table pointer is read afresh; callbacks may mutate the shader.
void RIFF_THISCALL Shader::bindCommonParameters() {
    vertexReposition = lookupParameter(vertexConstants, "g_repositionParams");
    pixelReposition = lookupParameter(pixelConstants, "g_repositionParams");
    fogParams = lookupParameter(pixelConstants, "gFogParams");
    fogColour = lookupParameter(pixelConstants, "gFogColour");
    fogHeightParams = lookupParameter(pixelConstants, "gFogHeightParams");
    alphaValue = lookupParameter(pixelConstants, "alphaValue");
    specularScale = lookupParameter(pixelConstants, "g_specularScale");
    specularPower = lookupParameter(pixelConstants, "g_specularPower");
    ambientColor = lookupParameter(pixelConstants, "g_ambientColor");
    diffuseColor = lookupParameter(pixelConstants, "g_diffuseColor");
    specularColor = lookupParameter(pixelConstants, "g_specularColor");
    shadowMapPos = lookupParameter(vertexConstants, "shadowMapPos");
    maskColor = lookupParameter(pixelConstants, "maskColor");
    shadowColor = lookupParameter(pixelConstants, "shadowColor");
    skinMatrixArray = lookupParameter(vertexConstants, "skinMatrixArray");
    morphAmounts = lookupParameter(vertexConstants, "g_morphAmounts");
}
}
