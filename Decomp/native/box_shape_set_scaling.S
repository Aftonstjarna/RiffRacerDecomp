# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x438b40,0x438c20); ECX=this; stack scaling pointer; RET 4.
.intel_syntax noprefix
.code32
.text
.equ ABS_FLOAT,0x426cf0
.global original_box_shape_set_scaling
original_box_shape_set_scaling:
    push   ebp
    mov.s ebp,esp
    and    esp,0xfffffff0
    sub    esp,0x38
    push   esi
    push   edi
    mov.s edi,ecx
    mov    esi,DWORD PTR [ebp+0x8]
    push   ecx
    movdqu xmm1,XMMWORD PTR [edi+0x1c]
    movaps xmm0,xmm1
    divss  xmm0,DWORD PTR [edi+0xc]
    movss  DWORD PTR [esp+0x10],xmm0
    movaps xmm0,xmm1
    shufps xmm0,xmm1,0x55
    divss  xmm0,DWORD PTR [edi+0x10]
    shufps xmm1,xmm1,0xaa
    divss  xmm1,DWORD PTR [edi+0x14]
    movaps XMMWORD PTR [esp+0x24],xmm0
    movss  xmm0,DWORD PTR [esi]
    movdqa XMMWORD PTR [esp+0x34],xmm1
    movss  DWORD PTR [esp],xmm0
    call ABS_FLOAT
    movss  xmm0,DWORD PTR [esi+0x4]
    fstp   DWORD PTR [esp+0x14]
    movss  DWORD PTR [esp],xmm0
    call ABS_FLOAT
    movss  xmm0,DWORD PTR [esi+0x8]
    fstp   DWORD PTR [esp+0x18]
    movss  DWORD PTR [esp],xmm0
    call ABS_FLOAT
    fstp   DWORD PTR [esp+0x1c]
    mov    DWORD PTR [esp+0x20],0x0
    add    esp,0x4
    movdqu xmm0,XMMWORD PTR [esp+0x10]
    mov    DWORD PTR [esp+0x1c],0x0
    movdqu XMMWORD PTR [edi+0xc],xmm0
    movss  xmm0,DWORD PTR [edi+0xc]
    mulss  xmm0,DWORD PTR [esp+0xc]
    movss  DWORD PTR [esp+0x10],xmm0
    movss  xmm0,DWORD PTR [edi+0x10]
    mulss  xmm0,DWORD PTR [esp+0x20]
    movss  DWORD PTR [esp+0x14],xmm0
    movss  xmm0,DWORD PTR [edi+0x14]
    mulss  xmm0,DWORD PTR [esp+0x30]
    movss  DWORD PTR [esp+0x18],xmm0
    movdqu xmm0,XMMWORD PTR [esp+0x10]
    movdqu XMMWORD PTR [edi+0x1c],xmm0
    pop    edi
    pop    esi
    mov.s esp,ebp
    pop    ebp
    ret    0x4
.section .note.GNU-stack,"",@progbits
