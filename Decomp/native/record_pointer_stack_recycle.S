# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x548b30, exclusive end 0x548b58.
.intel_syntax noprefix
.code32
.text
.global original_record_pointer_stack_recycle
original_record_pointer_stack_recycle:
    push ebp
    mov.s ebp, esp
    push esi
    mov esi, DWORD PTR [ebp+8]
    dec DWORD PTR [esi+0x20]
    mov eax, DWORD PTR [esi+0x20]
    mov edx, DWORD PTR [ecx+0x168]
    mov eax, DWORD PTR [esi+eax*4]
    mov DWORD PTR [ecx+edx*4+0x158], eax
    inc DWORD PTR [ecx+0x168]
    pop esi
    pop ebp
    ret 4
.section .note.GNU-stack,"",@progbits
