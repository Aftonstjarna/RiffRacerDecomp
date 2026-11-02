#include "render_helpers.hpp"
using namespace riff::recovered;

extern "C" {
void RIFF_CALLBACK_ABI original_ui_matrix_scale(Matrix3x4*, float, float, float);
ShaderBase32* RIFF_CALLBACK_ABI original_shader_base_ctor(ShaderBase32*);
void RIFF_CALLBACK_ABI original_shader_binding_cleanup(ShaderBindings32*);
void test_write(const char*, unsigned);
unsigned test_get_mxcsr();
void test_set_mxcsr(unsigned);
}

// Test-runtime support for compiler-emitted aggregate copies; not recovered code.
extern "C" void* memcpy(void* destination, const void* source, unsigned count) {
  auto* out = static_cast<unsigned char*>(destination);
  auto* in = static_cast<const unsigned char*>(source);
  for (unsigned i = 0; i != count; ++i) out[i] = in[i];
  return destination;
}

static void print(const char* s) {
  unsigned n = 0;
  while (s[n]) ++n;
  test_write(s, n);
}
static void hex(unsigned value) {
  char digits[9];
  for (unsigned i = 0; i != 8; ++i)
    digits[i] = "0123456789abcdef"[(value >> (28 - 4 * i)) & 15];
  digits[8] = '\n';
  test_write(digits, 9);
}
static unsigned bits(const float& value) {
  unsigned result;
  __builtin_memcpy(&result, &value, 4);
  return result;
}
static bool equal(const void* left, const void* right, unsigned bytes) {
  auto* a = static_cast<const unsigned char*>(left);
  auto* b = static_cast<const unsigned char*>(right);
  for (unsigned i = 0; i != bytes; ++i) if (a[i] != b[i]) return false;
  return true;
}
static unsigned random_state = 0x5a17e341;
static unsigned random_word() {
  random_state ^= random_state << 13;
  random_state ^= random_state >> 17;
  random_state ^= random_state << 5;
  return random_state;
}
static void set_bits(float& value, unsigned pattern) {
  // Do not return float here: i386's x87 return convention can quiet an sNaN
  // before either tested routine sees it, especially in the -O0 build.
  __builtin_memcpy(&value, &pattern, sizeof(value));
}
static unsigned matrix_cases = 0;
static bool matrix_case(const Matrix3x4& input, float x, float y, float z,
                        unsigned control) {
  Matrix3x4 expected = input, actual = input;
  test_set_mxcsr(control);
  original_ui_matrix_scale(&expected, x, y, z);
  const auto expected_flags = test_get_mxcsr();
  test_set_mxcsr(control);
  recovered_ui_matrix_scale(&actual, x, y, z);
  const auto actual_flags = test_get_mxcsr();
  ++matrix_cases;
  const bool same = equal(&expected, &actual, sizeof(actual)) && expected_flags == actual_flags;
  if (!same) {
    print("matrix case/control/input/factor/expected/actual/expected flags/actual flags:\n");
    hex(matrix_cases); hex(control); hex(bits(input.values[0])); hex(bits(x));
    for (unsigned i = 0; i != 12; ++i) if (bits(expected.values[i]) != bits(actual.values[i])) {
      hex(i); hex(bits(expected.values[i])); hex(bits(actual.values[i]));
    }
    hex(expected_flags); hex(actual_flags);
  }
  return same;
}
static bool test_matrix() {
  // Normal values, signed zeros, subnormals, infinities and quiet/signaling NaNs.
  const unsigned edge[] = {0, 0x80000000, 0x3f800000, 0xbf800000,
    1, 0x80000001, 0x007fffff, 0x00800000, 0x7f7fffff, 0xff7fffff,
    0x7f800000, 0xff800000, 0x7fc12345, 0xffc54321, 0x7f812345};
  const unsigned saved = test_get_mxcsr();
  bool ok = true;
  for (unsigned rounding = 0; rounding != 4 && ok; ++rounding) {
    for (unsigned flush = 0; flush != 2 && ok; ++flush) {
      const unsigned control = 0x1f80 | (rounding << 13) | (flush << 15);
      for (unsigned a : edge) for (unsigned b : edge) {
        Matrix3x4 input;
        for (unsigned i = 0; i != 12; ++i) set_bits(input.values[i], a);
        float factor;
        set_bits(factor, b);
        if (!matrix_case(input, factor, factor, factor, control)) {
          test_set_mxcsr(saved);
          return false;
        }
      }
      for (unsigned n = 0; n != 512 && ok; ++n) {
        Matrix3x4 input;
        for (auto& value : input.values) set_bits(value, random_word());
        float x, y, z;
        set_bits(x, random_word());
        set_bits(y, random_word());
        set_bits(z, random_word());
        ok = matrix_case(input, x, y, z, control);
      }
    }
  }
  test_set_mxcsr(saved);
  return ok && matrix_cases == 5896;
}

static bool test_constructor() {
  for (unsigned n = 0; n != 1024; ++n) {
    ShaderBase32 expected, actual;
    auto* bytes = reinterpret_cast<unsigned char*>(&expected);
    for (unsigned i = 0; i != sizeof(expected); ++i)
      bytes[i] = static_cast<unsigned char>(random_word());
    actual = expected;
    if (original_shader_base_ctor(&expected) != &expected) return false;
    if (recovered_shader_base_ctor(&actual) != &actual) return false;
    if (!equal(&expected, &actual, sizeof(actual))) return false;
  }
  return true;
}

struct TestBinding {
  ShaderBinding32 base;
  unsigned id;
};
static TestBinding objects[1680];
static ShaderBindings32 expected_tables, actual_tables;
static ShaderBindings32* active_tables;
static unsigned events[1680], expected_events[1680], event_count;
static bool mutate, overflow;
static void RIFF_CALLBACK_ABI record_call(ShaderBinding32* binding) {
  auto* object = reinterpret_cast<TestBinding*>(binding);
  if (event_count == 1680) { overflow = true; return; }
  events[event_count++] = object->id;
  if (mutate && event_count == 1) {
    // A callback alters not-yet-visited entries, including the current column.
    active_tables->tables[4][0] = nullptr;
    active_tables->tables[5][0] = &objects[1679].base;
    active_tables->tables[0][279] = &objects[17].base;
  }
}
static const BindingVtable32 vtable = {{0, 0, 0, 0}, record_call};
static bool test_bindings() {
  for (unsigned i = 0; i != 1680; ++i) objects[i] = {{&vtable}, i};
  for (unsigned mode = 0; mode != 5; ++mode) {
    for (auto& byte : expected_tables.unknown_prefix) byte = 0xa7;
    for (unsigned table = 0; table != 6; ++table) {
      for (unsigned column = 0; column != 280; ++column) {
        const unsigned index = table * 280 + column;
        auto* value = &objects[index].base;
        if (mode == 0 || (mode == 1 && index % 3 != 0)) value = nullptr;
        if (mode == 3) value = &objects[index % 11].base;
        expected_tables.tables[table][column] = value;
      }
    }
    actual_tables = expected_tables;
    mutate = mode == 4;
    event_count = 0; overflow = false; active_tables = &expected_tables;
    original_shader_binding_cleanup(&expected_tables);
    if (overflow) return false;
    const unsigned expected_count = event_count;
    for (unsigned i = 0; i != expected_count; ++i) expected_events[i] = events[i];
    event_count = 0; overflow = false; active_tables = &actual_tables;
    recovered_shader_binding_cleanup(&actual_tables);
    if (overflow || event_count != expected_count) return false;
    if (!equal(events, expected_events, event_count * sizeof(unsigned))) return false;
    if (!equal(&expected_tables, &actual_tables, sizeof(actual_tables))) return false;
  }
  return true;
}

extern "C" int test_main() {
  if (!test_matrix()) { print("FAIL: matrix values/MXCSR\n"); return 1; }
  if (!test_constructor()) { print("FAIL: base initialization\n"); return 2; }
  if (!test_bindings()) { print("FAIL: callback order or side effects\n"); return 3; }
  print("PASS: 5896 matrix cases (bits and MXCSR), 1024 initializers, 5 callback-table scenarios\n");
  return 0;
}
