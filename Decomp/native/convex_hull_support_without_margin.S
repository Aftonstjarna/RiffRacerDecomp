# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47cff0,0x47d0be); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.equ INITIAL_DOT,0xa06920
.global original_convex_hull_support_without_margin
original_convex_hull_support_without_margin:
    push   ebp
    mov.s    ebp,esp
    and    esp,0xfffffff0
    mov    edx,DWORD PTR [ebp+0x8]
    sub    esp,0x18
    movss  xmm4,DWORD PTR [INITIAL_DOT]
    push   esi
    push   edi
    mov.s    edi,ecx
    mov    DWORD PTR [edx],0x0
    mov    DWORD PTR [edx+0x4],0x0
    mov    DWORD PTR [edx+0x8],0x0
    mov    DWORD PTR [edx+0xc],0x0
    mov    esi,DWORD PTR [edi+0x5c]
    test   esi,esi
    jle L_47d0b4
    mov    eax,DWORD PTR [ebp+0xc]
    mov    ecx,DWORD PTR [edi+0x64]
    mov    DWORD PTR [esp+0x1c],0x0
    movss  xmm5,DWORD PTR [eax+0x4]
    movss  xmm6,DWORD PTR [eax]
    movss  xmm7,DWORD PTR [eax+0x8]
    {disp32} lea    ebx,[ebx+0x0]
L_47d050:
    movss  xmm0,DWORD PTR [ecx+0x4]
    movaps xmm3,xmm5
    mulss  xmm0,DWORD PTR [edi+0x10]
    movss  xmm2,DWORD PTR [ecx]
    mulss  xmm2,DWORD PTR [edi+0xc]
    movss  xmm1,DWORD PTR [ecx+0x8]
    mulss  xmm1,DWORD PTR [edi+0x14]
    mulss  xmm3,xmm0
    movss  DWORD PTR [esp+0x14],xmm0
    movaps xmm0,xmm6
    mulss  xmm0,xmm2
    movss  DWORD PTR [esp+0x10],xmm2
    movss  DWORD PTR [esp+0x18],xmm1
    addss  xmm3,xmm0
    movaps xmm0,xmm7
    mulss  xmm0,xmm1
    addss  xmm3,xmm0
    comiss xmm3,xmm4
    jbe L_47d0ae
    movdqu xmm0,XMMWORD PTR [esp+0x10]
    movaps xmm4,xmm3
    movdqu XMMWORD PTR [edx],xmm0
L_47d0ae:
    add    ecx,0x10
    dec    esi
    jne L_47d050
L_47d0b4:
    pop    edi
    mov.s    eax,edx
    pop    esi
    mov.s    esp,ebp
    pop    ebp
    ret    0x8
.section .note.GNU-stack,"",@progbits
