#ifndef RIFF_LUA_CONSTANT_STRING_NAME_HPP
#define RIFF_LUA_CONSTANT_STRING_NAME_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_FASTCALL __fastcall
#elif defined(__i386__)
#define RIFF_FASTCALL __attribute__((fastcall))
#else
#define RIFF_FASTCALL
#endif
namespace riff {
// Partial 32-bit Lua layouts; unobserved fields deliberately remain opaque.
struct LuaConstant { uint32_t value_address; uint32_t tag; };
struct LuaPrototype { uint32_t opaque[2]; uint32_t constants_address; };
// Original internal register ABI: ECX=prototype, EDX=operand, EAX=result.
const char* RIFF_FASTCALL constant_string_name(const LuaPrototype* prototype,
                                             uint32_t operand);
}
#endif
