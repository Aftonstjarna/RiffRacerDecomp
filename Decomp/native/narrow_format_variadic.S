.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x452ca0.
.global original_narrow_format_variadic
original_narrow_format_variadic:
    push ebp
    mov.s ebp,esp
    mov eax,DWORD PTR [ebp+0xc]
    push esi
    mov esi,DWORD PTR [ebp+0x10]
    test eax,eax
    je .Lfallback
    lea ecx,[ebp+0x14]
    push ecx
    push esi
    push -1
    push eax
    push DWORD PTR [ebp+0x8]
    call DWORD PTR [0x92d3bc]
    add esp,0x14
    cmp eax,-1
    jne .Ldone
.Lfallback:
    lea eax,[ebp+0x14]
    push eax
    push esi
    call DWORD PTR [0x92d3a8]
    add esp,0x8
.Ldone:
    pop esi
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
