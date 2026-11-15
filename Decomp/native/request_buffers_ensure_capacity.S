# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x509be0,0x509c46); subsequent INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_request_buffers_ensure_capacity
original_request_buffers_ensure_capacity:
    push   esi
    mov.s    esi,ecx
    mov    eax,0x78787879
    mov    edx,DWORD PTR [esi+0x14]
    lea    ecx,[esi+0xc]
    sub    edx,DWORD PTR [ecx]
    imul   edx
    sar    edx,0x5
    mov.s    eax,edx
    shr    eax,0x1f
    add.s    eax,edx
    cmp    eax,0x400
    jae L_509c0d
    push   0x400
    call   0x509dc0
L_509c0d:
    mov    eax,DWORD PTR [esi+0x20]
    lea    ecx,[esi+0x18]
    sub    eax,DWORD PTR [ecx]
    sar    eax,0x2
    cmp    eax,0x1000
    jae L_509c29
    push   0x1000
    call   0x426800
L_509c29:
    mov    eax,DWORD PTR [esi+0x8]
    sub    eax,DWORD PTR [esi]
    sar    eax,0x2
    cmp    eax,0x200
    jae L_509c44
    push   0x200
    mov.s    ecx,esi
    call   0x426800
L_509c44:
    pop    esi
    ret
.section .note.GNU-stack,"",@progbits
