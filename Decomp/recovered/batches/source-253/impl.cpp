#include "impl.hpp"
namespace riff {
// wsShaderSea constructor: original VA 0x577320, 533 bytes.
// The finalizer at 0x534ee8 passes a successful 0xcc-byte allocation in ECX.
// Normal-path effects only: Windows SEH registration and unwind are not
// portable rendering behavior and are not reimplemented here.
static uint32_t find(ConstantTable* table, const char* name) {
    return reinterpret_cast<FindByName>(table->vtable[9])(table, 0, name);
}
SeaShader* SEA_THIS SeaShader::construct() {
    initializeBase();
    vtable = 0xa015d0;
    state58 = 0;
    state80 = 0;
    state84 = 0;
    ShaderManager* manager = seaShaderManager;
    flagC8 = 0;
    for (unsigned i = 0; i != 16; ++i) matrix[i] = (i % 5 == 0) ? 1.0f : 0.0f;
    vertexShader = manager->vertexShader;
    pixelShader = manager->pixelShader;
    vertexConstants = manager->vertexConstants;
    pixelConstants = manager->pixelConstants;
    // Re-read each table field: callbacks can change the next request's table.
    worldViewProjection = find(vertexConstants, "matWorldViewProj");
    world = find(vertexConstants, "matWorld");
    eyePosition = find(pixelConstants, "eyePositionWS");
    sunAngle = find(pixelConstants, "g_sunAng");
    timer = find(vertexConstants, "gTimer");
    bumpScale = find(vertexConstants, "gBumpScale");
    textureScale = find(vertexConstants, "gTextureScale");
    commonHandles[9] = find(pixelConstants, "g_ambientColor"); // +3c
    commonHandles[11] = find(pixelConstants, "g_specularColor"); // +44
    waveScale = find(vertexConstants, "gWaveScale");
    bumpSpeed = find(vertexConstants, "gBumpSpeed");
    // Overwrites +3c and +44; direct results remain observable to callbacks.
    bindCommonParameters();
    return this;
}
}
