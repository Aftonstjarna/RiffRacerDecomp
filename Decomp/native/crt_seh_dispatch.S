# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete exception-dispatch wrapper VA [0x8f9ce9,0x8f9d0c).
.intel_syntax noprefix
.code32
.text
.global original_crt_seh_dispatch
.equ except_handler4_common_thunk,0x8f9ef4
original_crt_seh_dispatch:
    push ebp
    mov.s ebp,esp
    push DWORD PTR [ebp+0x14]
    push DWORD PTR [ebp+0x10]
    push DWORD PTR [ebp+0xc]
    push DWORD PTR [ebp+0x8]
    push 0x8f8958
    push 0xbaabc0
    call except_handler4_common_thunk
    add esp,0x18
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
