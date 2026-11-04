#pragma once
using u32 = unsigned int;
using u16 = unsigned short;
// Original 32-bit MSVC basic_string<WCHAR> layout. WCHAR is 16 bits,
// independently of the native platform's wchar_t. Capacity >=8 selects heap.
struct WideString {
    union Storage { u16 inline_data[8]; u16* heap; } storage;
    u32 length;
    u32 capacity;
};
static_assert(sizeof(WideString)==24, "requires i386 layout");
extern "C" WideString* __attribute__((thiscall)) original_wide_assign_substring(
    WideString* destination, const WideString* source, u32 position, u32 count);
extern "C" WideString* __attribute__((thiscall)) original_wide_prefix_construct(
    const WideString* source, WideString* destination, u32 unused, u32 maximum);
extern "C" WideString* __attribute__((thiscall)) recovered_wide_prefix_construct(
    const WideString* source, WideString* destination, u32 unused, u32 maximum);
