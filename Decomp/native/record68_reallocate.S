# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x509dc0,0x509e5c); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_record68_reallocate
original_record68_reallocate:
    push   ebp
    mov.s    ebp,esp
    push   ebx
    push   esi
    mov    esi,DWORD PTR [ebp+0x8]
    mov.s    ebx,ecx
    push   edi
    xor.s    edi,edi
    test   esi,esi
    je L_509df9
    cmp    esi,0x3c3c3c3
    ja L_509df3
    mov.s    eax,esi
    shl    eax,0x4
    add.s    eax,esi
    shl    eax,0x2
    push   eax
    call   DWORD PTR ds:0x92d4b4
    mov.s    edi,eax
    add    esp,0x4
    test   edi,edi
    jne L_509df9
L_509df3:
    call   DWORD PTR ds:0x92d164
L_509df9:
    push   DWORD PTR [ebp+0x8]
    mov    edx,DWORD PTR [ebx+0x4]
    mov    ecx,DWORD PTR [ebx]
    sub    esp,0x8
    push   edi
    call   0x509e60
    mov    ecx,DWORD PTR [ebx+0x4]
    mov    eax,0x78787879
    sub    ecx,DWORD PTR [ebx]
    add    esp,0x10
    imul   ecx
    mov    eax,DWORD PTR [ebx]
    sar    edx,0x5
    mov.s    ecx,edx
    shr    ecx,0x1f
    add.s    ecx,edx
    mov    DWORD PTR [ebp+0x8],ecx
    test   eax,eax
    je L_509e39
    push   eax
    call   DWORD PTR ds:0x92d4b0
    mov    ecx,DWORD PTR [ebp+0x8]
    add    esp,0x4
L_509e39:
    mov.s    eax,esi
    mov    DWORD PTR [ebx],edi
    shl    eax,0x4
    add.s    eax,esi
    lea    eax,[edi+eax*4]
    mov    DWORD PTR [ebx+0x8],eax
    mov.s    eax,ecx
    shl    eax,0x4
    add.s    eax,ecx
    lea    eax,[edi+eax*4]
    pop    edi
    pop    esi
    mov    DWORD PTR [ebx+0x4],eax
    pop    ebx
    pop    ebp
    ret    0x4
.section .note.GNU-stack,"",@progbits
