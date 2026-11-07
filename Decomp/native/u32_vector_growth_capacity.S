# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x50dfe0,0x50e018); both returns included, adjacent INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_u32_vector_growth_capacity
original_u32_vector_growth_capacity:
 push ebp
 mov.s ebp,esp
 mov edx,DWORD PTR [ecx+8]
 mov eax,0x3fffffff
 sub edx,DWORD PTR [ecx]
 sar edx,2
 mov.s ecx,edx
 shr ecx,1
 sub.s eax,ecx
 cmp.s eax,edx
 jae growth_fits
 xor.s edx,edx
 cmp edx,DWORD PTR [ebp+8]
 cmovb edx,DWORD PTR [ebp+8]
 mov.s eax,edx
 pop ebp
 ret 4
growth_fits:
 add.s edx,ecx
 cmp edx,DWORD PTR [ebp+8]
 cmovb edx,DWORD PTR [ebp+8]
 mov.s eax,edx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
