#include "impl.hpp"
extern "C" const char* __attribute__((fastcall)) original_lua_constant_string_name(
    const riff::LuaPrototype*, uint32_t);
extern "C" void test_write(const char*, unsigned);
static riff::LuaConstant constants[512];
static riff::LuaConstant saved[512];
static unsigned char string_object[48];
static riff::LuaPrototype prototype;
static uint32_t address(const void* p) { return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(p)); }
static bool check(uint32_t operand, const riff::LuaPrototype* p, bool string_result,
                  uint32_t value) {
    const char* original = original_lua_constant_string_name(p, operand);
    const char* recovered = riff::constant_string_name(p, operand);
    if (string_result) {
        const char* expected = reinterpret_cast<const char*>(static_cast<uintptr_t>(value + 16u));
        if (original != expected || recovered != expected) return false;
    } else {
        // No fixture maps the original literal: verify its evidenced address
        // directly, then verify the relocated recovered literal's contents.
        if (address(original) != 0x9f99d0u || recovered[0] != '?' || recovered[1] != 0) return false;
    }
    if (prototype.opaque[0] != 0x12345678u || prototype.opaque[1] != 0x87654321u ||
        prototype.constants_address != address(constants)) return false;
    for (unsigned i=0;i<512;++i)
        if (constants[i].value_address != saved[i].value_address || constants[i].tag != saved[i].tag) return false;
    for (unsigned i=0;i<sizeof(string_object);++i)
        if (string_object[i] != static_cast<unsigned char>(i*7u)) return false;
    return true;
}
extern "C" int test_main() {
    prototype.opaque[0]=0x12345678u; prototype.opaque[1]=0x87654321u;
    prototype.constants_address=address(constants);
    for (unsigned i=0;i<sizeof(string_object);++i) string_object[i]=static_cast<unsigned char>(i*7u);
    const uint32_t tags[] = {0,1,2,3,4,5,6,0xffffffffu,0x104u};
    for (unsigned t=0;t<sizeof(tags)/sizeof(tags[0]);++t) {
        for (unsigned i=0;i<512;++i) {
            constants[i].tag=tags[t]; constants[i].value_address=address(string_object);
            saved[i]=constants[i];
        }
        for (uint32_t op=0;op<512;++op)
            if (!check(op,&prototype,(op&256u)!=0 && tags[t]==4,address(string_object))) return 1;
        if (!check(0x300u,&prototype,tags[t]==4,address(string_object))) return 2;
        if (!check(0x20000100u,&prototype,tags[t]==4,address(string_object))) return 3;
    }
    // Register operands must not dereference ECX at all.
    if (!check(0,0,false,0) || !check(0xfffffeffu,0,false,0)) return 4;
    // The string pointer is computed, not read or validated, including wrap.
    const uint32_t values[]={0,1,0xfffffff0u,0xffffffffu};
    for (unsigned i=0;i<4;++i) {
        constants[0].tag=4; constants[0].value_address=values[i]; saved[0]=constants[0];
        if (!check(256,&prototype,true,values[i])) return 5;
    }
    test_write("lua constant string tests passed\n",33);
    return 0;
}
