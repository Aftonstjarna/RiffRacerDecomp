.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x438870.
.global original_convex_internal_shape_serialize
original_convex_internal_shape_serialize:
    push   ebp
    mov.s    ebp,esp
    push   ebx
    mov    ebx,DWORD PTR [ebp+0xc]
    push   esi
    mov.s    esi,ecx
    mov.s    ecx,ebx
    push   edi
    mov    eax,DWORD PTR [ebx]
    push   esi
    call   DWORD PTR [eax+0x24]
    mov    edx,DWORD PTR [ebx]
    mov.s    ecx,ebx
    push   eax
    mov    DWORD PTR [ebp+0xc],eax
    call   DWORD PTR [edx+0x18]
    mov    edi,DWORD PTR [ebp+0x8]
    mov    DWORD PTR [edi],eax
    test   eax,eax
    je     after_name
    mov    eax,DWORD PTR [ebx]
    mov.s    ecx,ebx
    push   DWORD PTR [ebp+0xc]
    call   DWORD PTR [eax+0x2c]
after_name:
    mov    eax,DWORD PTR [esi+0x4]
    mov    DWORD PTR [edi+0x4],eax
    mov    eax,DWORD PTR [esi+0x1c]
    mov    DWORD PTR [edi+0x1c],eax
    mov    eax,DWORD PTR [esi+0x20]
    mov    DWORD PTR [edi+0x20],eax
    mov    eax,DWORD PTR [esi+0x24]
    mov    DWORD PTR [edi+0x24],eax
    mov    eax,DWORD PTR [esi+0x28]
    mov    DWORD PTR [edi+0x28],eax
    mov    eax,DWORD PTR [esi+0xc]
    mov    DWORD PTR [edi+0xc],eax
    mov    eax,DWORD PTR [esi+0x10]
    mov    DWORD PTR [edi+0x10],eax
    mov    eax,DWORD PTR [esi+0x14]
    mov    DWORD PTR [edi+0x14],eax
    mov    eax,DWORD PTR [esi+0x18]
    mov    DWORD PTR [edi+0x18],eax
    mov    eax,DWORD PTR [esi+0x2c]
    mov    DWORD PTR [edi+0x2c],eax
    mov    eax,0x9f9950
    pop    edi
    pop    esi
    pop    ebx
    pop    ebp
    ret    0x8
.section .note.GNU-stack,"",@progbits
