#include "impl.hpp"
// Original 0x576f00..0x577039, thiscall, RET 4, returns this.
// Callers at 0x5346c2/6fc/736/770 select variants 0,1,2,3 respectively.
// No null checks: manager and both parameter objects must be valid.
CarLights* RIFF_THIS CarLights::construct(uint32_t selectedVariant) {
    initializeBase();
    ShaderManager* manager = shader_manager;
    variant = selectedVariant;
    vtable = 0xa0145c;
    const uint32_t vertex = manager->vertexProgram;
    for (unsigned row=0; row<4; ++row)
        for (unsigned column=0; column<4; ++column)
            transform[row][column] = row==column ? 1.0f : 0.0f;
    vertexProgram = vertex;
    pixelProgram = manager->pixelProgram;
    vertexParameters = manager->vertexParameters;
    pixelParameters = manager->pixelParameters;
    worldViewProjection = vertexParameters->vtable->namedParameter(
        vertexParameters, 0, "matWorldViewProj");
    lightColour = pixelParameters->vtable->namedParameter(
        pixelParameters, 0, "lightColour");
    initializeCommonParameters();
    return this;
}
// Windows SEH registration/cookie machinery is compiler/runtime infrastructure.
// This portable source models normal completion only; it does not emulate unwind.
