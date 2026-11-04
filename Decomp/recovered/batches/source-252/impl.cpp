#include "impl.hpp"
// VA 0x578350..0x5784e7, thiscall, EAX=this, RET 8.
// Callers 0x534610/64c/688 allocate 0xb8 bytes and pass (0,0),(1,0),(1,1).
// Only the low argument bytes are stored; treating them as bool would lose
// observed behavior for noncanonical values. Padding +5a/+5b stays untouched.
CarGlass::CarGlass(uint8_t first,uint8_t second) { construct(first,second); }
CarGlass* RIFF_THIS CarGlass::construct(uint8_t first,uint8_t second) {
    initializeBase();
    flag58=first;
    vtable=0xa016d8;
    flag59=second;
    member5c=0;
    unknownB4=0;
    ShaderManager* manager=shader_manager;
    const uint32_t vertex=manager->vertexProgram;
    for(unsigned r=0;r<4;++r)
        for(unsigned c=0;c<4;++c)transform[r][c]=r==c?1.0f:0.0f;
    vertexProgram=vertex;
    pixelProgram=manager->pixelProgram;
    vertexParameters=manager->vertexParameters;
    pixelParameters=manager->pixelParameters;
    // Reload resource fields after each external call, as the original does.
    // These five calls are COM stdcall slot +24, not the enumerating helper.
    worldViewProjection=vertexParameters->vtable->namedParameter(vertexParameters,0,"matWorldViewProj");
    inverseView=vertexParameters->vtable->namedParameter(vertexParameters,0,"matInvView");
    cameraPosition=vertexParameters->vtable->namedParameter(vertexParameters,0,"vCameraPos");
    diffuse=pixelParameters->vtable->namedParameter(pixelParameters,0,"diffuse");
    reflectiveness=pixelParameters->vtable->namedParameter(pixelParameters,0,"reflectiveness");
    initializeCommonParameters();
    return this;
}
// Normal-return recovery only. The original registers FS:[0] with handler
// 0x9080c6 and construction states -1/0/1. Windows fault dispatch/unwinding
// and member/base destruction on failure are external, unresolved behavior.
// No null validation, ownership changes, or rendering behavior is invented.
