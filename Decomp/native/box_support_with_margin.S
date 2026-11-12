# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4388f0,0x4389a1); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.equ SIGN_MASK,0xa071e0
.global original_box_support_with_margin
original_box_support_with_margin:
# ECX=this; stack arguments: output vector, direction vector; callee pops 8.
 push   ebp
 mov.s    ebp,esp
 and    esp,0xfffffff0
 sub    esp,0x1c
 push   esi
 mov.s    esi,ecx
 # Re-read the virtual margin getter; preserve all three calls.
 mov    eax,DWORD PTR [esi]
 movdqu xmm0,XMMWORD PTR [esi+0x1c]
 mov    eax,DWORD PTR [eax+0x28]
 movdqu XMMWORD PTR [esp+0x10],xmm0
 call   eax
 mov    eax,DWORD PTR [esi]
 mov.s    ecx,esi
 fstp   DWORD PTR [esp+0xc]
 mov    eax,DWORD PTR [eax+0x28]
 call   eax
 mov    eax,DWORD PTR [esi]
 mov.s    ecx,esi
 fstp   DWORD PTR [esp+0x8]
 mov    eax,DWORD PTR [eax+0x28]
 call   eax
 mov    eax,DWORD PTR [ebp+0xc]
 xorps  xmm4,xmm4
 fadd   DWORD PTR [esp+0x10]
 movss  xmm0,DWORD PTR [eax+0x8]
 comiss xmm0,xmm4
 movss  xmm2,DWORD PTR [esp+0x14]
 movss  xmm1,DWORD PTR [esp+0x18]
 addss  xmm2,DWORD PTR [esp+0x8]
 addss  xmm1,DWORD PTR [esp+0xc]
 movss  xmm3,DWORD PTR [SIGN_MASK]
 fstp   DWORD PTR [esp+0x10]
 # COMISS/JAE preserves the original unordered and signed-zero handling.
 jae    L_438963
 xorps  xmm1,xmm3
L_438963:
 movss  xmm0,DWORD PTR [eax+0x4]
 comiss xmm0,xmm4
 jae    L_438970
 xorps  xmm2,xmm3
L_438970:
 movss  xmm0,DWORD PTR [eax]
 comiss xmm0,xmm4
 movss  xmm0,DWORD PTR [esp+0x10]
 jae    L_438982
 xorps  xmm0,xmm3
L_438982:
 mov    eax,DWORD PTR [ebp+0x8]
 pop    esi
 movss  DWORD PTR [eax],xmm0
 movss  DWORD PTR [eax+0x4],xmm2
 movss  DWORD PTR [eax+0x8],xmm1
 mov    DWORD PTR [eax+0xc],0x0
 mov.s    esp,ebp
 pop    ebp
 ret    0x8
.section .note.GNU-stack,"",@progbits
