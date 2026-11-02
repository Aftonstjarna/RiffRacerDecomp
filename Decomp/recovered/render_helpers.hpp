#pragma once

// Readable reconstructions of three original x86 routines. Not byte-matched C++.
namespace riff::recovered {
using Word32 = unsigned int;
static_assert(sizeof(Word32) == 4 && sizeof(float) == 4);

struct Matrix3x4 {
  float values[12];
};

// Field names describe observed offsets, not recovered original member names.
struct ShaderBase32 {
  Word32 vtable;
  Word32 unknown_04;
  Word32 unknown_08;
  Word32 fields_0c_through_38[12];
  Word32 unknown_3c;
  Word32 unknown_40;
  Word32 field_44;
  Word32 unknown_48;
  Word32 unknown_4c;
  Word32 field_50;
  Word32 field_54;
};
static_assert(sizeof(ShaderBase32) == 0x58);
inline constexpr Word32 original_wsShader_vtable = 0x009fe7e0;

// The only callback contract established here is vtable slot 4, ECX=this,
// no stack arguments, ignored return value. Other slots remain untyped.
#if defined(__GNUC__) && defined(__i386__)
#define RIFF_CALLBACK_ABI __attribute__((thiscall))
#else
#error "The original callback ABI adapter currently supports GCC-compatible i386 only"
#endif
struct ShaderBinding32;
using BindingOperation = void (RIFF_CALLBACK_ABI *)(ShaderBinding32*);
struct BindingVtable32 {
  Word32 unknown_slots[4];
  BindingOperation slot_4;
};
struct ShaderBinding32 {
  const BindingVtable32* vtable;
};
struct ShaderBindings32 {
  unsigned char unknown_prefix[0xe1c];
  ShaderBinding32* tables[6][280];
};
static_assert(sizeof(void*) == 4, "These layouts describe the original x86 game");
static_assert(__builtin_offsetof(BindingVtable32, slot_4) == 0x10);
static_assert(__builtin_offsetof(ShaderBindings32, tables) == 0xe1c);
static_assert(sizeof(ShaderBindings32::tables[0]) == 0x460);

// C exports allow inspection of compiled function sections. Their calling
// convention is the test/platform default, not a claim of original MSVC ABI.
extern "C" {
void recovered_ui_matrix_scale(Matrix3x4*, float x, float y, float z);
ShaderBase32* recovered_shader_base_ctor(ShaderBase32*);
void recovered_shader_binding_cleanup(ShaderBindings32*);
}
} // namespace riff::recovered
