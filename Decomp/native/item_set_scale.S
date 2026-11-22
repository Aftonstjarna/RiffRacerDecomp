.intel_syntax noprefix
.code32
.text
# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x448a10,0x448afc); RET 4, followed by INT3 padding and a new entry at 0x448b00.
# Item setScale: stores the two floats from the pointer argument at this+0xAC/+0xB0,
# propagates their scaled products to each 0x14-byte attachment in +0x184..+0x188
# (setting dirty bit 8 when a stored pair changes), then invokes vtable slot 0x74 on
# this and on each pointer in +0x178..+0x17C. Derived from original instructions and
# direct callers; it earns reference-assembly evidence only, not matching-source credit.
.global original_item_set_scale
original_item_set_scale:
.L448a10:
 push   ebp
.L448a11:
 {load} mov    ebp,esp
.L448a13:
 and    esp,0xfffffff8
.L448a16:
 mov    edx,DWORD PTR [ebp+0x8]
.L448a19:
 sub    esp,0x8
.L448a1c:
 mov    eax,DWORD PTR [edx]
.L448a1e:
 push   esi
.L448a1f:
 push   edi
.L448a20:
 {load} mov    edi,ecx
.L448a22:
 mov    DWORD PTR [edi+0xac],eax
.L448a28:
 mov    eax,DWORD PTR [edx+0x4]
.L448a2b:
 mov    edx,DWORD PTR [edi+0x184]
.L448a31:
 mov    DWORD PTR [edi+0xb0],eax
.L448a37:
 cmp    edx,DWORD PTR [edi+0x188]
.L448a3d:
 je .L448acd
.L448a43:
 mov    ecx,DWORD PTR [edx]
.L448a45:
 test   ecx,ecx
.L448a47:
 je .L448abe
.L448a49:
 movss  xmm0,DWORD PTR [edi+0xc4]
.L448a51:
 mulss  xmm0,DWORD PTR [edi+0xac]
.L448a59:
 movss  xmm2,DWORD PTR [edi+0xe4]
.L448a61:
 movss  xmm1,DWORD PTR [edi+0xc8]
.L448a69:
 mulss  xmm1,DWORD PTR [edi+0xb0]
.L448a71:
 movss  xmm3,DWORD PTR [edi+0xe8]
.L448a79:
 mulss  xmm2,xmm0
.L448a7d:
 movss  xmm0,DWORD PTR [ecx+0x70]
.L448a82:
 mulss  xmm3,xmm1
.L448a86:
 ucomiss xmm0,xmm2
.L448a89:
 movss  DWORD PTR [esp+0x8],xmm2
.L448a8f:
 movss  DWORD PTR [esp+0xc],xmm3
.L448a95:
 lahf
.L448a96:
 test   ah,0x44
.L448a99:
 jp .L448aa9
.L448a9b:
 movss  xmm0,DWORD PTR [ecx+0x74]
.L448aa0:
 ucomiss xmm0,xmm3
.L448aa3:
 lahf
.L448aa4:
 test   ah,0x44
.L448aa7:
 jnp .L448ab0
.L448aa9:
 or     DWORD PTR [ecx+0x170],0x8
.L448ab0:
 mov    eax,DWORD PTR [esp+0x8]
.L448ab4:
 mov    DWORD PTR [ecx+0x70],eax
.L448ab7:
 mov    eax,DWORD PTR [esp+0xc]
.L448abb:
 mov    DWORD PTR [ecx+0x74],eax
.L448abe:
 add    edx,0x14
.L448ac1:
 cmp    edx,DWORD PTR [edi+0x188]
.L448ac7:
 jne .L448a43
.L448acd:
 mov    eax,DWORD PTR [edi]
.L448acf:
 {load} mov    ecx,edi
.L448ad1:
 call   DWORD PTR [eax+0x74]
.L448ad4:
 mov    esi,DWORD PTR [edi+0x178]
.L448ada:
 cmp    esi,DWORD PTR [edi+0x17c]
.L448ae0:
 je .L448af4
.L448ae2:
 mov    ecx,DWORD PTR [esi]
.L448ae4:
 mov    eax,DWORD PTR [ecx]
.L448ae6:
 call   DWORD PTR [eax+0x74]
.L448ae9:
 add    esi,0x4
.L448aec:
 cmp    esi,DWORD PTR [edi+0x17c]
.L448af2:
 jne .L448ae2
.L448af4:
 pop    edi
.L448af5:
 pop    esi
.L448af6:
 {load} mov    esp,ebp
.L448af8:
 pop    ebp
.L448af9:
 ret    0x4
