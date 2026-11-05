# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256:
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x44e120,0x44e13d); both returns included; INT3 padding excluded.
# ECX=destination, EDX=source, [entry ESP+4]=UTF-16 element count.
# Caller pops count. Zero returns destination without accessing either buffer.
# Nonzero doubles count modulo 2^32 and calls CRT memcpy; no overlap protection.
.intel_syntax noprefix
.code32
.text
.global original_wide_copy_elements
original_wide_copy_elements:
 push ebp
 {load} mov ebp,esp
 mov eax,DWORD PTR [ebp+8]
 test eax,eax
 jne .Lcopy
 {load} mov eax,ecx
 pop ebp
 ret
.Lcopy:
 {load} add eax,eax
 push eax
 push edx
 push ecx
 call crt_memcpy
 add esp,12
 pop ebp
 ret
.equ crt_memcpy,0x8f8d66
.section .note.GNU-stack,"",@progbits
