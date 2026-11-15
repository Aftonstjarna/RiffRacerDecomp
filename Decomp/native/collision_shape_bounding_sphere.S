# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA [0x47c060,0x47c183); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_collision_shape_bounding_sphere
original_collision_shape_bounding_sphere:
    push   ebp
    mov.s    ebp,esp
    and    esp,0xfffffff0
    sub    esp,0x88
    mov    eax,ds:0xbaabc0
    xor.s    eax,esp
    mov    DWORD PTR [esp+0x84],eax
    mov    eax,DWORD PTR [ebp+0x8]
    push   esi
    mov.s    esi,ecx
    mov    DWORD PTR [esp+0x8],eax
    push   edi
    mov    edi,DWORD PTR [ebp+0xc]
    lea    ecx,[esp+0x48]
    call   0x438480
    mov    eax,DWORD PTR [esi]
    lea    ecx,[esp+0x38]
    push   ecx
    lea    ecx,[esp+0x2c]
    push   ecx
    lea    ecx,[esp+0x50]
    push   ecx
    mov.s    ecx,esi
    call   DWORD PTR [eax+0x4]
    movss  xmm2,DWORD PTR [esp+0x3c]
    movss  xmm1,DWORD PTR [esp+0x38]
    subss  xmm1,DWORD PTR [esp+0x28]
    subss  xmm2,DWORD PTR [esp+0x2c]
    movss  xmm0,DWORD PTR [esp+0x40]
    subss  xmm0,DWORD PTR [esp+0x30]
    push   ecx
    mulss  xmm1,xmm1
    mulss  xmm2,xmm2
    mulss  xmm0,xmm0
    addss  xmm1,xmm2
    addss  xmm1,xmm0
    movss  DWORD PTR [esp],xmm1
    call   0x426d60
    movss  xmm0,DWORD PTR ds:0xa06508
    add    esp,0x4
    movss  xmm2,DWORD PTR [esp+0x38]
    movss  xmm1,DWORD PTR [esp+0x28]
    mulss  xmm2,xmm0
    mov    eax,DWORD PTR [esp+0xc]
    mulss  xmm1,xmm0
    mov    ecx,DWORD PTR [esp+0x8c]
    fmul   DWORD PTR ds:0xa06508
    mov    DWORD PTR [esp+0x1c],0x0
    addss  xmm2,xmm1
    movss  xmm1,DWORD PTR [esp+0x2c]
    mulss  xmm1,xmm0
    fstp   DWORD PTR [edi]
    pop    edi
    movss  DWORD PTR [esp+0xc],xmm2
    movss  xmm2,DWORD PTR [esp+0x38]
    mulss  xmm2,xmm0
    pop    esi
    xor.s    ecx,esp
    addss  xmm2,xmm1
    movss  xmm1,DWORD PTR [esp+0x28]
    mulss  xmm1,xmm0
    movss  DWORD PTR [esp+0xc],xmm2
    movss  xmm2,DWORD PTR [esp+0x38]
    mulss  xmm2,xmm0
    addss  xmm2,xmm1
    movss  DWORD PTR [esp+0x10],xmm2
    movdqu xmm0,XMMWORD PTR [esp+0x8]
    movdqu XMMWORD PTR [eax],xmm0
    call   0x8f8958
    mov.s    esp,ebp
    pop    ebp
    ret    0x8
.section .note.GNU-stack,"",@progbits
