# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x438fe0,0x439075); both return paths included.
.intel_syntax noprefix
.code32
.text
.equ SIGN_MASK,0xa071e0
.global original_box_point_inside_tolerance
original_box_point_inside_tolerance:
    push   ebp
    {load} mov ebp,esp
    and    esp,0xfffffff0
    sub    esp,0x10
    movdqu xmm1,XMMWORD PTR [ecx+0x1c]
    mov    eax,DWORD PTR [ebp+0x8]
    movss  xmm2,DWORD PTR [ebp+0xc]
    movaps xmm0,xmm2
    movdqa XMMWORD PTR [esp],xmm1
    addss  xmm0,xmm1
    movss  xmm4,DWORD PTR [eax]
    comiss xmm0,xmm4
    jb .Lreject
    movss  xmm3,DWORD PTR [SIGN_MASK]
    xorps  xmm1,xmm3
    subss  xmm1,xmm2
    comiss xmm4,xmm1
    jb .Lreject
    movss  xmm1,DWORD PTR [esp+0x4]
    movss  xmm4,DWORD PTR [eax+0x4]
    movaps xmm0,xmm1
    addss  xmm0,xmm2
    comiss xmm0,xmm4
    jb .Lreject
    xorps  xmm1,xmm3
    subss  xmm1,xmm2
    comiss xmm4,xmm1
    jb .Lreject
    movss  xmm1,DWORD PTR [esp+0x8]
    movss  xmm4,DWORD PTR [eax+0x8]
    movaps xmm0,xmm1
    addss  xmm0,xmm2
    comiss xmm0,xmm4
    jb .Lreject
    xorps  xmm1,xmm3
    subss  xmm1,xmm2
    comiss xmm4,xmm1
    jb .Lreject
    mov    al,0x1
    {load} mov esp,ebp
    pop    ebp
    ret    0x8
.Lreject:
    {load} xor al,al
    {load} mov esp,ebp
    pop    ebp
    ret    0x8
