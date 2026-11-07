# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x509e60,0x509eeb); register ABI ECX=first, EDX=last, [ESP+4]=destination; caller cleans stack.
.intel_syntax noprefix
.code32
.text
.global original_record68_range_copy
original_record68_range_copy:
    push   ebp
    {load} mov    ebp,esp
    push   ebx
    {load} mov    ebx,edx
    {load} cmp    ecx,ebx
    je .L509ee5
    mov    edx,DWORD PTR [ebp+0x8]
    push   esi
    push   edi
    lea    esi,[ecx+0x14]
    lea    edi,[edx+0x14]
.L509e75:
    test   edx,edx
    je .L509ece
    mov    eax,DWORD PTR [esi-0x14]
    mov    DWORD PTR [edx],eax
    mov    eax,DWORD PTR [esi-0x10]
    mov    DWORD PTR [edi-0x10],eax
    mov    eax,DWORD PTR [esi-0xc]
    mov    DWORD PTR [edi-0xc],eax
    mov    eax,DWORD PTR [esi-0x8]
    mov    DWORD PTR [edi-0x8],eax
    mov    eax,DWORD PTR [esi-0x4]
    mov    DWORD PTR [edi-0x4],eax
    mov    eax,DWORD PTR [esi]
    mov    DWORD PTR [edi],eax
    mov    eax,DWORD PTR [esi+0x4]
    mov    DWORD PTR [edi+0x4],eax
    mov    eax,DWORD PTR [esi+0x8]
    mov    DWORD PTR [edi+0x8],eax
    mov    eax,DWORD PTR [esi+0xc]
    mov    DWORD PTR [edi+0xc],eax
    mov    eax,DWORD PTR [esi+0x10]
    mov    DWORD PTR [edi+0x10],eax
    mov    eax,DWORD PTR [esi+0x14]
    mov    DWORD PTR [edi+0x14],eax
    mov    eax,DWORD PTR [esi+0x18]
    mov    DWORD PTR [edi+0x18],eax
    mov    eax,DWORD PTR [esi+0x1c]
    mov    DWORD PTR [edi+0x1c],eax
    movdqu xmm0,XMMWORD PTR [esi+0x20]
    movdqu XMMWORD PTR [edi+0x20],xmm0
.L509ece:
    add    esi,0x44
    add    edx,0x44
    add    edi,0x44
    lea    ecx,[esi-0x14]
    {load} cmp    ecx,ebx
    jne .L509e75
    pop    edi
    pop    esi
    {load} mov    eax,edx
    pop    ebx
    pop    ebp
    ret
.L509ee5:
    mov    eax,DWORD PTR [ebp+0x8]
    pop    ebx
    pop    ebp
    ret
.section .note.GNU-stack,"",@progbits
