.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x49c050.
.global original_wide_entry_growth_policy
original_wide_entry_growth_policy:
 push ebp
 {load} mov ebp, esp
 push esi
 mov esi, DWORD PTR [ecx+8]
 mov eax, 0x92492493
 sub esi, DWORD PTR [ecx]
 imul esi
 mov eax, 0x09249249
 {load} add edx, esi
 sar edx, 4
 {load} mov esi, edx
 shr esi, 31
 {load} add esi, edx
 {load} mov ecx, esi
 shr ecx, 1
 {load} sub eax, ecx
 {load} cmp eax, esi
 jae .Lnormal
 {load} xor esi, esi
 cmp esi, DWORD PTR [ebp+8]
 cmovb esi, DWORD PTR [ebp+8]
 {load} mov eax, esi
 pop esi
 pop ebp
 ret 4
.Lnormal:
 {load} add esi, ecx
 cmp esi, DWORD PTR [ebp+8]
 cmovb esi, DWORD PTR [ebp+8]
 {load} mov eax, esi
 pop esi
 pop ebp
 ret 4
