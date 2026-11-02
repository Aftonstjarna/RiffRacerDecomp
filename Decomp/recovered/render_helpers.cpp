#include "render_helpers.hpp"

namespace riff::recovered {
// elMatrix.scaleBy, MethodDef 0x06001651, original VA [0x458810,0x4588a2).
void recovered_ui_matrix_scale(Matrix3x4* matrix, float x, float y, float z) {
  for (unsigned i = 0; i != 3; ++i) matrix->values[i] *= x;
  for (unsigned i = 3; i != 6; ++i) matrix->values[i] *= y;
  for (unsigned i = 6; i != 9; ++i) matrix->values[i] *= z;
  // Translation values 9..11 are deliberately untouched.
}

// wsShader base initialization, original VA [0x5421b0,0x542222).
ShaderBase32* recovered_shader_base_ctor(ShaderBase32* shader) {
  shader->vtable = original_wsShader_vtable;
  for (auto& field : shader->fields_0c_through_38) field = 0;
  shader->field_44 = 0;
  shader->field_50 = 0;
  shader->field_54 = 0;
  return shader;
}

// Original VA [0x52f5b0,0x52f5f3). Column order is observable through callbacks.
void recovered_shader_binding_cleanup(ShaderBindings32* shader) {
  for (unsigned column = 0; column != 280; ++column) {
    for (unsigned table = 0; table != 6; ++table) {
      auto* binding = shader->tables[table][column];
      if (binding != nullptr) binding->vtable->slot_4(binding);
    }
  }
  // The original does not clear the tables or deduplicate shared pointers.
}
} // namespace riff::recovered
