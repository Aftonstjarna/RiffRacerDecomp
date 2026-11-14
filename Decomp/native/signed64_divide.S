# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f9830,0x8f98da); excludes INT3 padding.
.intel_syntax noprefix
.code32
.text
.global original_signed64_divide
original_signed64_divide:
    push   edi
    push   esi
    push   ebx
    xor.s    edi,edi
    mov    eax,DWORD PTR [esp+0x14]
    or.s     eax,eax
    jge L8f9851
    inc    edi
    mov    edx,DWORD PTR [esp+0x10]
    neg    eax
    neg    edx
    sbb    eax,0x0
    mov    DWORD PTR [esp+0x14],eax
    mov    DWORD PTR [esp+0x10],edx
L8f9851:
    mov    eax,DWORD PTR [esp+0x1c]
    or.s     eax,eax
    jge L8f986d
    inc    edi
    mov    edx,DWORD PTR [esp+0x18]
    neg    eax
    neg    edx
    sbb    eax,0x0
    mov    DWORD PTR [esp+0x1c],eax
    mov    DWORD PTR [esp+0x18],edx
L8f986d:
    or.s     eax,eax
    jne L8f9889
    mov    ecx,DWORD PTR [esp+0x18]
    mov    eax,DWORD PTR [esp+0x14]
    xor.s    edx,edx
    div    ecx
    mov.s    ebx,eax
    mov    eax,DWORD PTR [esp+0x10]
    div    ecx
    mov.s    edx,ebx
    jmp L8f98ca
L8f9889:
    mov.s    ebx,eax
    mov    ecx,DWORD PTR [esp+0x18]
    mov    edx,DWORD PTR [esp+0x14]
    mov    eax,DWORD PTR [esp+0x10]
L8f9897:
    shr    ebx,1
    rcr    ecx,1
    shr    edx,1
    rcr    eax,1
    or.s     ebx,ebx
    jne L8f9897
    div    ecx
    mov.s    esi,eax
    mul    DWORD PTR [esp+0x1c]
    mov.s    ecx,eax
    mov    eax,DWORD PTR [esp+0x18]
    mul    esi
    add.s    edx,ecx
    jb L8f98c5
    cmp    edx,DWORD PTR [esp+0x14]
    ja L8f98c5
    jb L8f98c6
    cmp    eax,DWORD PTR [esp+0x10]
    jbe L8f98c6
L8f98c5:
    dec    esi
L8f98c6:
    xor.s    edx,edx
    mov.s    eax,esi
L8f98ca:
    dec    edi
    jne L8f98d4
    neg    edx
    neg    eax
    sbb    edx,0x0
L8f98d4:
    pop    ebx
    pop    esi
    pop    edi
    ret    0x10
.section .note.GNU-stack,"",@progbits
