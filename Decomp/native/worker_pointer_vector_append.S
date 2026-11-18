.intel_syntax noprefix
.code32
.text
.global original_worker_pointer_vector_append
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x42c2a0 through 0x42c302 inclusive.
original_worker_pointer_vector_append:
    push ebp
    {load} mov ebp,esp
    push esi
    {load} mov esi,ecx
    push edi
    mov edi,DWORD PTR [ebp+8]
    mov eax,DWORD PTR [esi+4]
    {load} cmp edi,eax
    jae .Lexternal
    mov ecx,DWORD PTR [esi]
    {load} cmp ecx,edi
    ja .Lexternal
    {load} sub edi,ecx
    sar edi,2
    cmp eax,DWORD PTR [esi+8]
    jne .Linternal_ready
    push ecx
    {load} mov ecx,esi
    call grow_pointers
.Linternal_ready:
    mov ecx,DWORD PTR [esi+4]
    test ecx,ecx
    je .Lfinish
    mov eax,DWORD PTR [esi]
    mov eax,DWORD PTR [eax+edi*4]
    mov DWORD PTR [ecx],eax
    add DWORD PTR [esi+4],4
    pop edi
    pop esi
    pop ebp
    ret 4
.Lexternal:
    cmp eax,DWORD PTR [esi+8]
    jne .Lexternal_ready
    push ecx
    {load} mov ecx,esi
    call grow_pointers
.Lexternal_ready:
    mov ecx,DWORD PTR [esi+4]
    test ecx,ecx
    je .Lfinish
    mov eax,DWORD PTR [edi]
    mov DWORD PTR [ecx],eax
.Lfinish:
    add DWORD PTR [esi+4],4
    pop edi
    pop esi
    pop ebp
    ret 4
.equ grow_pointers,0x429ce0
.section .note.GNU-stack,"",@progbits
