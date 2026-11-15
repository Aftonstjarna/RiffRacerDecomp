# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x427110, complete range [0x427110,0x427136).
.intel_syntax noprefix
.code32
.text
.global original_convex_callback_filter_test
original_convex_callback_filter_test:
    push ebp
    mov.s ebp,esp
    mov edx,DWORD PTR [ebp+8]
    mov ax,WORD PTR [edx+4]
    test WORD PTR [ecx+6],ax
    je filter_reject
    mov ax,WORD PTR [edx+6]
    test WORD PTR [ecx+4],ax
    je filter_reject
    mov al,1
    pop ebp
    ret 4
filter_reject:
    xor.s al,al
    pop ebp
    ret 4
