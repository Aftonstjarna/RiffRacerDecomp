# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x450c40.
.intel_syntax noprefix
.code32
.text
.global original_text_colour_forward
.equ base_colour,0x448500
.equ visual_colour,0x442f50
original_text_colour_forward:
    push ebp
    {load} mov ebp,esp
    push esi
    push DWORD PTR [ebp+8]
    {load} mov esi,ecx
    call base_colour
    cmp DWORD PTR [esi+0x10],3
    je .Ldone
    push DWORD PTR [ebp+8]
    mov ecx,DWORD PTR [esi+0x1c4]
    call visual_colour
.Ldone:
    pop esi
    pop ebp
    ret 4
.section .note.GNU-stack,"",@progbits
