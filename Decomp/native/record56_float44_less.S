# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Entire original function [0x426ee0,0x426ef9); no embedded instruction bytes.
.intel_syntax noprefix
.code32
.text
.global original_record56_float44_less
original_record56_float44_less:
    push ebp
    {load} mov ebp,esp
    mov eax,DWORD PTR [ebp+0xc]
    mov ecx,DWORD PTR [ebp+8]
    movss xmm0,DWORD PTR [eax+0x2c]
    {load} xor eax,eax
    comiss xmm0,DWORD PTR [ecx+0x2c]
    seta al
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
