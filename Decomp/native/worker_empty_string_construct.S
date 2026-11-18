.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4571b0.
.global original_worker_empty_string_construct
original_worker_empty_string_construct:
    push ebp
    {load} mov ebp,esp
    push ecx
    push esi
    mov esi,DWORD PTR [ebp+8]
    {load} mov ecx,esi
    push 0
    push 0x9998bc
    mov DWORD PTR [ebp-4],0
    mov DWORD PTR [esi+0x14],0xf
    mov DWORD PTR [esi+0x10],0
    mov BYTE PTR [esi],0
    call string_assign
    {load} mov eax,esi
    pop esi
    {load} mov esp,ebp
    pop ebp
    ret
.equ string_assign,0x416520
.section .note.GNU-stack,"",@progbits
