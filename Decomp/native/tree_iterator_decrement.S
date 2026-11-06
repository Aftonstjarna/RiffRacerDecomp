# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4235a0,0x4235fe). Tree iterator predecessor.
.intel_syntax noprefix
.code32
.text
.global original_tree_iterator_decrement
original_tree_iterator_decrement:
    {load} mov edx, ecx
    mov eax, DWORD PTR [edx]
    cmp BYTE PTR [eax+0xd], 0
    je .Lordinary
    mov eax, DWORD PTR [eax+8]
    mov DWORD PTR [edx], eax
    {load} mov eax, edx
    ret
.Lordinary:
    mov ecx, DWORD PTR [eax]
    cmp BYTE PTR [ecx+0xd], 0
    jne .Lparents
    mov eax, DWORD PTR [ecx+8]
    cmp BYTE PTR [eax+0xd], 0
    jne .Lstore
.Lright:
    {load} mov ecx, eax
    mov eax, DWORD PTR [ecx+8]
    cmp BYTE PTR [eax+0xd], 0
    je .Lright
    mov DWORD PTR [edx], ecx
    {load} mov eax, edx
    ret
.Lparents:
    mov ecx, DWORD PTR [eax+4]
    cmp BYTE PTR [ecx+0xd], 0
    jne .Lcheck
    {disp8} lea esp, [esp+0]
.Lclimb:
    mov eax, DWORD PTR [edx]
    cmp eax, DWORD PTR [ecx]
    jne .Lcheck
    mov DWORD PTR [edx], ecx
    mov ecx, DWORD PTR [ecx+4]
    cmp BYTE PTR [ecx+0xd], 0
    je .Lclimb
.Lcheck:
    mov eax, DWORD PTR [edx]
    cmp BYTE PTR [eax+0xd], 0
    jne .Ldone
.Lstore:
    mov DWORD PTR [edx], ecx
.Ldone:
    {load} mov eax, edx
    ret
.section .note.GNU-stack,"",@progbits
