# Mechanically transcribed reference evidence, NOT high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x426d90,0x426ea4); both returns included; INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_vector3_normalize
original_vector3_normalize:
 push   ebp
 mov.s    ebp,esp
 sub    esp,0x8
 push   esi
 mov.s    esi,ecx
 xorps  xmm1,xmm1
 push   ecx
 movss  xmm0,DWORD PTR [esi]
 movss  DWORD PTR [ebp-0x4],xmm0
 subss  xmm0,xmm1
 movss  DWORD PTR [esp],xmm0
 call fn_426cf0
 movss  xmm0,DWORD PTR [epsilon]
 add    esp,0x4
 fstp   DWORD PTR [ebp-0x8]
 comiss xmm0,DWORD PTR [ebp-0x8]
 jb L426e37
 movss  xmm0,DWORD PTR [esi+0x4]
 xorps  xmm1,xmm1
 subss  xmm0,xmm1
 push   ecx
 movss  DWORD PTR [esp],xmm0
 call fn_426cf0
 movss  xmm0,DWORD PTR [epsilon]
 add    esp,0x4
 fstp   DWORD PTR [ebp-0x8]
 comiss xmm0,DWORD PTR [ebp-0x8]
 jb L426e37
 movss  xmm0,DWORD PTR [esi+0x8]
 xorps  xmm1,xmm1
 subss  xmm0,xmm1
 push   ecx
 movss  DWORD PTR [esp],xmm0
 call fn_426cf0
 movss  xmm0,DWORD PTR [epsilon]
 add    esp,0x4
 fstp   DWORD PTR [ebp-0x8]
 comiss xmm0,DWORD PTR [ebp-0x8]
 jb L426e37
 mov    DWORD PTR [esi],0x0
 mov    DWORD PTR [esi+0x4],0x0
 mov    DWORD PTR [esi+0x8],0x3f800000
 pop    esi
 mov.s    esp,ebp
 pop    ebp
 ret
L426e37:
 movss  xmm3,DWORD PTR [ebp-0x4]
 movss  xmm2,DWORD PTR [esi+0x4]
 movaps xmm0,xmm3
 movss  xmm1,DWORD PTR [esi+0x8]
 mulss  xmm2,xmm2
 push   ecx
 mulss  xmm0,xmm3
 mulss  xmm1,xmm1
 addss  xmm2,xmm0
 addss  xmm2,xmm1
 movss  DWORD PTR [esp],xmm2
 call fn_426d60
 fld1
 add    esp,0x4
 fdivrp st(1),st
 movss  xmm0,DWORD PTR [ebp-0x4]
 fstp   DWORD PTR [ebp-0x8]
 movss  xmm1,DWORD PTR [ebp-0x8]
 mulss  xmm0,xmm1
 movss  DWORD PTR [esi],xmm0
 movaps xmm0,xmm1
 mulss  xmm0,DWORD PTR [esi+0x4]
 movss  DWORD PTR [esi+0x4],xmm0
 movss  xmm0,DWORD PTR [esi+0x8]
 mulss  xmm0,xmm1
 movss  DWORD PTR [esi+0x8],xmm0
 pop    esi
 mov.s    esp,ebp
 pop    ebp
 ret
.equ fn_426cf0,0x426cf0
.equ fn_426d60,0x426d60
.equ epsilon,0xa0641c
.section .note.GNU-stack,"",@progbits
