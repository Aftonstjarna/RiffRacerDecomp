#ifndef RIFF_SEA_HPP
#define RIFF_SEA_HPP
#include <stdint.h>
#ifdef _MSC_VER
#define SEA_THIS __thiscall
#define SEA_STD __stdcall
#else
#define SEA_THIS __attribute__((thiscall))
#define SEA_STD __attribute__((stdcall))
#endif
namespace riff {
struct ConstantTable;
typedef uint32_t (SEA_STD *FindByName)(ConstantTable*, uint32_t, const char*);
struct ConstantTable { void** vtable; };
// External manager dependency; offsets 0..917 are outside this recovery.
struct ShaderManager { uint8_t unknown[0x918]; uint32_t vertexShader;
    ConstantTable* vertexConstants; uint32_t pixelShader; ConstantTable* pixelConstants; };
extern ShaderManager* seaShaderManager;
struct SeaShader {
    uint32_t vtable;                         // +00 original identity token
    uint32_t vertexShader, pixelShader;      // +04, +08
    uint32_t reserved0c;
    ConstantTable* vertexConstants;          // +10
    ConstantTable* pixelConstants;           // +14
    uint32_t commonHandles[16];              // +18..54 (external helper)
    uint32_t state58;
    uint32_t worldViewProjection, world, eyePosition, timer; // +5c..68
    uint32_t textureScale, bumpScale, sunAngle, waveScale, bumpSpeed; // +6c..7c
    uint32_t state80, state84;
    float matrix[16];                        // +88..c4, identity-shaped; runtime use unconfirmed
    uint8_t flagC8;                         // +c8, flag meaning unconfirmed
    uint8_t untouchedTail[3];                // caller allocates 0xcc bytes
    // Dependencies 0x5421b0 / 0x542230. Supply accepted originals in tests;
    // their recovery is deliberately outside this bounded implementation.
    void SEA_THIS initializeBase();
    void SEA_THIS bindCommonParameters();
    SeaShader* SEA_THIS construct();          // original no-argument thiscall, EAX=this
};
}
#endif
