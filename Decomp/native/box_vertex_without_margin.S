.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x438d30.
.global original_box_vertex_without_margin
original_box_vertex_without_margin:
    push   ebp
    {load} mov ebp,esp
    and    esp,0xfffffff0
    sub    esp,0x1c
    movdqu xmm3,XMMWORD PTR [ecx+0x1c]
    push   esi
    mov    esi,DWORD PTR [ebp+0x8]
    mov    edx,0x1
    {load} mov    ecx,esi
    mov    DWORD PTR [esp+0x1c],0x0
    and    ecx,0x1
    {load} mov    eax,edx
    {load} sub    eax,ecx
    movd   xmm0,ecx
    {load} mov    ecx,esi
    cvtdq2ps xmm0,xmm0
    sar    ecx,1
    {load} and    ecx,edx
    sar    esi,0x2
    {load} and    esi,edx
    movd   xmm1,eax
    {load} mov    eax,edx
    cvtdq2ps xmm1,xmm1
    {load} sub    eax,ecx
    {load} sub    edx,esi
    mulss  xmm0,xmm3
    mulss  xmm1,xmm3
    movd   xmm2,eax
    cvtdq2ps xmm2,xmm2
    mov    eax,DWORD PTR [ebp+0xc]
    subss  xmm1,xmm0
    movd   xmm0,ecx
    cvtdq2ps xmm0,xmm0
    movss  DWORD PTR [esp+0x10],xmm1
    movaps xmm1,xmm3
    shufps xmm1,xmm3,0x55
    mulss  xmm0,xmm1
    mulss  xmm2,xmm1
    movd   xmm1,edx
    cvtdq2ps xmm1,xmm1
    subss  xmm2,xmm0
    shufps xmm3,xmm3,0xaa
    movd   xmm0,esi
    cvtdq2ps xmm0,xmm0
    pop    esi
    mulss  xmm1,xmm3
    mulss  xmm0,xmm3
    movss  DWORD PTR [esp+0x10],xmm2
    subss  xmm1,xmm0
    movss  DWORD PTR [esp+0x14],xmm1
    movdqu xmm0,XMMWORD PTR [esp+0xc]
    movdqu XMMWORD PTR [eax],xmm0
    {load} mov esp,ebp
    pop    ebp
    ret    0x8
