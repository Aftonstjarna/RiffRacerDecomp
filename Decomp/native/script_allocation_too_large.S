# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f7cf0,0x4f7d0a); surrounding INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_allocation_too_large
.equ script_error,0x486ab0
.equ allocation_error_literal,0x9fdb34
original_script_allocation_too_large:
    push ebp
    mov.s ebp,esp
    and esp,-8
    push allocation_error_literal
    push ecx
    call script_error
    add esp,8
    xor.s eax,eax
    mov.s esp,ebp
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
