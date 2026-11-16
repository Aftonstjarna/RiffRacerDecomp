#ifndef RIFF_FLAG_SELECTED_PRODUCT_HPP
#define RIFF_FLAG_SELECTED_PRODUCT_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_REGISTER_CALL __fastcall
#elif defined(__i386__)
#define RIFF_REGISTER_CALL __attribute__((fastcall))
#else
#define RIFF_REGISTER_CALL
#endif

// Partial object view only: no claim about the original class name or full size.
// Original VA 0x55d190, RVA 0x15d190, length 36. ECX=this, EDX=multiplier,
// EAX=result; no stack parameters or writes. The observed caller at 0x55bfdb
// stores the result at this+0x6d00; that store is outside this method's scope.
struct FlagSelectedProduct {
    uint8_t unknown_prefix[0x6cec];
    uint32_t flags;
    uint32_t ordinary_factor;
    uint32_t common_factor;

    uint32_t RIFF_REGISTER_CALL selected_product(uint32_t multiplier) const;
};
static_assert(offsetof(FlagSelectedProduct, flags) == 0x6cec, "flags offset");
static_assert(offsetof(FlagSelectedProduct, ordinary_factor) == 0x6cf0, "ordinary offset");
static_assert(offsetof(FlagSelectedProduct, common_factor) == 0x6cf4, "common offset");
static_assert(sizeof(FlagSelectedProduct) == 0x6cf8, "partial view size");
#endif
