.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, NOT high-level source recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x47c270, end exclusive 0x47c2ad. No branch/data tables.
.global original_collision_shape_serialize_single
original_collision_shape_serialize_single:
    push ebp
    {load} mov ebp, esp
    push ebx
    {load} mov ebx, ecx
    push esi
    push edi
    mov eax, DWORD PTR [ebx]
    call DWORD PTR [eax+0x2c]
    mov edi, DWORD PTR [ebp+8]
    {load} mov ecx, edi
    push 1
    push eax
    mov edx, DWORD PTR [edi]
    call DWORD PTR [edx+0x0c]
    mov edx, DWORD PTR [ebx]
    {load} mov esi, eax
    push edi
    {load} mov ecx, ebx
    push DWORD PTR [esi+8]
    call DWORD PTR [edx+0x30]
    mov edx, DWORD PTR [edi]
    {load} mov ecx, edi
    push ebx
    push 0x50414853
    push eax
    push esi
    call DWORD PTR [edx+0x10]
    pop edi
    pop esi
    pop ebx
    pop ebp
    ret 4
.section .note.GNU-stack,"",@progbits
