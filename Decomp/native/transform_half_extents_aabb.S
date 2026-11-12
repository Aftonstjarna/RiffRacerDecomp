# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x47aec0,0x47b03b); original register/stack ABI retained.
.intel_syntax noprefix
.code32
.text
.equ ABS_MATRIX,0x47ad90
.equ CHECK_COOKIE,0x8f8958
.global original_transform_half_extents_aabb
original_transform_half_extents_aabb:
 push   ebp
 mov.s    ebp,esp
 and    esp,0xfffffff0
 sub    esp,0x78
 mov    eax,[0xbaabc0]
 xor.s    eax,esp
 mov    DWORD PTR [esp+0x74],eax
 movss  xmm0,DWORD PTR [ecx]
 mov    eax,DWORD PTR [ebp+0xc]
 addss  xmm0,xmm1
 push   esi
 push   edi
 mov    edi,DWORD PTR [ebp+0x8]
 mov.s    esi,edx
 mov    DWORD PTR [esp+0x20],eax
 lea    eax,[esp+0x4c]
 movss  DWORD PTR [esp+0x24],xmm0
 movss  xmm0,DWORD PTR [ecx+0x4]
 addss  xmm0,xmm1
 push   eax
 movss  DWORD PTR [esp+0x30],xmm0
 movss  xmm0,DWORD PTR [ecx+0x8]
 mov.s    ecx,esi
 addss  xmm0,xmm1
 movss  DWORD PTR [esp+0x2c],xmm0
 call ABS_MATRIX
 movss  xmm1,DWORD PTR [esp+0x2c]
 movss  xmm6,DWORD PTR [esp+0x24]
 movss  xmm0,DWORD PTR [esp+0x4c]
 movss  xmm7,DWORD PTR [esp+0x50]
 movss  xmm5,DWORD PTR [esp+0x28]
 movdqu xmm2,XMMWORD PTR [esi+0x30]
 mov    eax,DWORD PTR [esp+0x20]
 mulss  xmm0,xmm6
 mov    ecx,DWORD PTR [esp+0x7c]
 movss  xmm4,DWORD PTR [esp+0x60]
 movaps xmm3,xmm2
 mulss  xmm7,xmm1
 mov    DWORD PTR [esp+0x1c],0x0
 mulss  xmm4,xmm1
 addss  xmm7,xmm0
 shufps xmm3,xmm2,0x55
 movss  xmm0,DWORD PTR [esp+0x54]
 mulss  xmm0,xmm5
 movdqa XMMWORD PTR [esp+0x30],xmm2
 addss  xmm7,xmm0
 movaps xmm0,xmm2
 movss  xmm2,DWORD PTR [esp+0x70]
 mulss  xmm2,xmm1
 subss  xmm0,xmm7
 movss  DWORD PTR [esp+0x10],xmm0
 movss  xmm0,DWORD PTR [esp+0x5c]
 mulss  xmm0,xmm6
 addss  xmm4,xmm0
 movss  xmm0,DWORD PTR [esp+0x64]
 mulss  xmm0,xmm5
 addss  xmm4,xmm0
 movaps xmm0,xmm3
 subss  xmm0,xmm4
 addss  xmm4,xmm3
 movss  DWORD PTR [esp+0x14],xmm0
 movss  xmm0,DWORD PTR [esp+0x6c]
 mulss  xmm0,xmm6
 addss  xmm2,xmm0
 movss  xmm0,DWORD PTR [esp+0x74]
 mulss  xmm0,xmm5
 movdqa xmm5,XMMWORD PTR [esp+0x30]
 movaps xmm1,xmm5
 addss  xmm7,xmm5
 addss  xmm2,xmm0
 shufps xmm1,xmm5,0xaa
 movaps xmm0,xmm1
 subss  xmm0,xmm2
 addss  xmm2,xmm1
 movss  DWORD PTR [esp+0x18],xmm0
 movdqu xmm0,XMMWORD PTR [esp+0x10]
 mov    DWORD PTR [esp+0x1c],0x0
 movss  DWORD PTR [esp+0x10],xmm7
 movdqu XMMWORD PTR [edi],xmm0
 pop    edi
 movss  DWORD PTR [esp+0x10],xmm4
 movss  DWORD PTR [esp+0x14],xmm2
 movdqu xmm0,XMMWORD PTR [esp+0xc]
 pop    esi
 xor.s    ecx,esp
 movdqu XMMWORD PTR [eax],xmm0
 call CHECK_COOKIE
 mov.s    esp,ebp
 pop    ebp
 ret
.section .note.GNU-stack,"",@progbits
