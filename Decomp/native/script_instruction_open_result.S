.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x486150.
.global original_script_instruction_open_result
original_script_instruction_open_result:
 {load} mov eax, ecx
 and eax, 0x3f
 cmp eax, 0x1c
 jl .Lzero
 cmp eax, 0x1e
 jle .Lcheck
 cmp eax, 0x22
 jne .Lzero
.Lcheck:
 and ecx, 0xff800000
 neg ecx
 {load} sbb ecx, ecx
 lea eax, [ecx+1]
 ret
.Lzero:
 {load} xor eax, eax
 ret
.section .note.GNU-stack,"",@progbits
