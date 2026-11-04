#pragma once
using WideUnit = unsigned short;
using WideSize = unsigned int;
struct WideString {
    union Storage { WideUnit inline_data[8]; WideUnit* heap; } storage;
    WideSize length;
    WideSize capacity;
};
static_assert(sizeof(WideUnit) == 2, "Windows WCHAR width");
static_assert(__builtin_offsetof(WideString, length) == 16, "original layout");
static_assert(__builtin_offsetof(WideString, capacity) == 20, "original layout");
// Port integration supplies the nonreturning equivalent of std::_Xout_of_range.
extern "C" [[noreturn]] void recovered_wide_out_of_range(const char* message);
extern "C" WideString* __attribute__((thiscall)) recovered_wide_truncate(WideString*, WideSize);
extern "C" WideString* __attribute__((thiscall)) original_wide_truncate(WideString*, WideSize);
