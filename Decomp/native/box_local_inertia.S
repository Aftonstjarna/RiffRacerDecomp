# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x47b070; end exclusive 0x47b0f3.
.intel_syntax noprefix
.code32
.text
.global original_box_local_inertia
original_box_local_inertia:
    push   ebp
    mov.s    ebp,esp
    and    esp,0xfffffff8
    movss  xmm1,DWORD PTR [ebp+0x8]
    divss  xmm1,DWORD PTR [0xa0676c]
    mov    eax,DWORD PTR [ebp+0xc]
    movdqu xmm3,XMMWORD PTR [ecx+0x1c]
    movss  xmm0,DWORD PTR [0xa06618]
    movaps xmm2,xmm3
    movaps xmm4,xmm3
    shufps xmm2,xmm3,0x55
    movss  xmm3,DWORD PTR [ecx+0x24]
    mulss  xmm2,xmm0
    mov    DWORD PTR [eax+0xc],0x0
    mulss  xmm3,xmm0
    mulss  xmm4,xmm0
    mulss  xmm2,xmm2
    mulss  xmm3,xmm3
    movaps xmm0,xmm2
    mulss  xmm4,xmm4
    addss  xmm0,xmm3
    mulss  xmm0,xmm1
    movss  DWORD PTR [eax],xmm0
    movaps xmm0,xmm4
    addss  xmm0,xmm3
    addss  xmm4,xmm2
    mulss  xmm0,xmm1
    mulss  xmm4,xmm1
    movss  DWORD PTR [eax+0x4],xmm0
    movss  DWORD PTR [eax+0x8],xmm4
    mov.s    esp,ebp
    pop    ebp
    ret    0x8
.section .note.GNU-stack,"",@progbits
