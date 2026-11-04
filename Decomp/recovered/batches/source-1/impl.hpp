#ifndef RIFF_INLINE_SWAP_HPP
#define RIFF_INLINE_SWAP_HPP
// Storage-only helper: requires 16 accessible bytes per operand unless a
// no-access early return applies. Aliasing, including partial overlap, is allowed.
void narrow_inline_swap(void* first, void* second);
#endif
