# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47d5a0,0x47d709); adjacent INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_sphere_support_with_margin
original_sphere_support_with_margin:
 push   ebp
 mov.s    ebp,esp
 and    esp,0xfffffff0
 sub    esp,0x48
 mov    eax,[0xbaabc0]
 xor.s    eax,esp
 mov    DWORD PTR [esp+0x44],eax
 mov    eax,DWORD PTR [ecx]
 lea    edx,[esp+0x28]
 push   esi
 mov    esi,DWORD PTR [ebp+0xc]
 push   edi
 mov    eax,DWORD PTR [eax+0x3c]
 mov    edi,DWORD PTR [ebp+0x8]
 push   esi
 push   edx
 mov    DWORD PTR [esp+0x10],ecx
 call   eax
 movdqu xmm0,XMMWORD PTR [eax]
 movdqu XMMWORD PTR [edi],xmm0
 movdqu xmm2,XMMWORD PTR [esi]
 movaps xmm3,xmm2
 movdqa XMMWORD PTR [esp+0x10],xmm2
 shufps xmm3,xmm2,0x55
 movaps xmm1,xmm2
 movaps xmm0,xmm3
 mulss  xmm1,xmm2
 mulss  xmm0,xmm3
 movaps xmm4,xmm2
 shufps xmm4,xmm2,0xaa
 movaps XMMWORD PTR [esp+0x20],xmm3
 addss  xmm1,xmm0
 movaps XMMWORD PTR [esp+0x30],xmm4
 movaps xmm0,xmm4
 mulss  xmm0,xmm4
 addss  xmm1,xmm0
 movss  xmm0,DWORD PTR [0xa063fc]
 comiss xmm0,xmm1
 jbe loc_47d642
 movss  xmm0,DWORD PTR [0xa068ac]
 movaps xmm2,xmm0
 movaps xmm3,xmm0
 movaps xmm4,xmm0
 movdqa XMMWORD PTR [esp+0x10],xmm2
 movaps XMMWORD PTR [esp+0x20],xmm3
 movaps XMMWORD PTR [esp+0x30],xmm4
loc_47d642:
 movaps xmm1,xmm2
 movaps xmm0,xmm3
 mulss  xmm0,xmm3
 push   ecx
 mulss  xmm1,xmm2
 addss  xmm1,xmm0
 movaps xmm0,xmm4
 mulss  xmm0,xmm4
 addss  xmm1,xmm0
 movss  DWORD PTR [esp],xmm1
 call   0x426d60
 fld1
 add    esp,0x4
 fdivrp st(1),st
 mov    ecx,DWORD PTR [esp+0x8]
 mov    eax,DWORD PTR [ecx]
 mov    eax,DWORD PTR [eax+0x28]
 movdqa xmm1,XMMWORD PTR [esp+0x10]
 fstp   DWORD PTR [esp+0xc]
 movss  xmm0,DWORD PTR [esp+0xc]
 mulss  xmm1,xmm0
 movdqa XMMWORD PTR [esp+0x10],xmm1
 movaps xmm1,XMMWORD PTR [esp+0x20]
 mulss  xmm1,xmm0
 movaps XMMWORD PTR [esp+0x20],xmm1
 movaps xmm1,XMMWORD PTR [esp+0x30]
 mulss  xmm1,xmm0
 movaps XMMWORD PTR [esp+0x30],xmm1
 call   eax
 movdqa xmm1,XMMWORD PTR [esp+0x10]
 mov.s    eax,edi
 fstp   DWORD PTR [esp+0x8]
 movss  xmm0,DWORD PTR [esp+0x8]
 mulss  xmm1,xmm0
 mov    ecx,DWORD PTR [esp+0x4c]
 addss  xmm1,DWORD PTR [edi]
 movss  DWORD PTR [edi],xmm1
 movaps xmm1,XMMWORD PTR [esp+0x20]
 mulss  xmm1,xmm0
 addss  xmm1,DWORD PTR [edi+0x4]
 movss  DWORD PTR [edi+0x4],xmm1
 movaps xmm1,XMMWORD PTR [esp+0x30]
 mulss  xmm1,xmm0
 addss  xmm1,DWORD PTR [edi+0x8]
 movss  DWORD PTR [edi+0x8],xmm1
 pop    edi
 pop    esi
 xor.s    ecx,esp
 call   0x8f8958
 mov.s    esp,ebp
 pop    ebp
 ret    0x8
.section .note.GNU-stack,"",@progbits
