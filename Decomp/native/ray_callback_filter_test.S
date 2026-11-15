.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4270e0, complete function through 0x427105 inclusive.
.global original_ray_callback_filter_test
original_ray_callback_filter_test:
    push ebp
    mov.s ebp, esp
    mov edx, DWORD PTR [ebp+8]
    mov ax, WORD PTR [edx+4]
    test WORD PTR [ecx+14], ax
    je filter_reject
    mov ax, WORD PTR [edx+6]
    test WORD PTR [ecx+12], ax
    je filter_reject
    mov al, 1
    pop ebp
    ret 4
filter_reject:
    xor.s al, al
    pop ebp
    ret 4
.section .note.GNU-stack,"",@progbits
