# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x55d190,0x55d1b4); both RET paths included; INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_flag_selected_product
original_flag_selected_product:
 test DWORD PTR [ecx+0x6cec],0x4000
 mov eax,DWORD PTR [ecx+0x6cf4]
 je .Lordinary
 imul eax,edx
 shl eax,2
 ret
.Lordinary:
 imul eax,DWORD PTR [ecx+0x6cf0]
 imul eax,edx
 ret
.section .note.GNU-stack,"",@progbits
