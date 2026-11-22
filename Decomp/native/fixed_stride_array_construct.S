# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x442bd0,0x442cb1); instruction-contiguous extent, INT3 padding excluded.
# Fixed-stride array construct/assign helper called by resource initialization: element stride at +0x00, pointer range +0x08..+0x10, allocator state at +0x14, operator new via 0x8F87C8, range construct via 0x42C2A0 and reallocation via 0x426800. Element semantics are not established by this function alone.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x442bd0..0x442cb1
.intel_syntax noprefix
.code32
.text
.global original_fixed_stride_array_construct
original_fixed_stride_array_construct:
.L442bd0:
 push   ebp
.L442bd1:
 {load} mov    ebp,esp
.L442bd3:
 push   ebx
.L442bd4:
 mov    ebx,DWORD PTR [ebp+0xc]
.L442bd7:
 push   esi
.L442bd8:
 {load} mov    esi,ecx
.L442bda:
 mov    ecx,DWORD PTR [ebp+0x8]
.L442bdd:
 push   edi
.L442bde:
 {load} cmp    ecx,ebx
.L442be0:
 je .L442bf6
.L442be2:
 push   ecx
.L442be3:
 call   DWORD PTR [0x92d4b4]
.L442be9:
 add    esp,0x4
.L442bec:
 inc    DWORD PTR [esi+0x24]
.L442bef:
 pop    edi
.L442bf0:
 pop    esi
.L442bf1:
 pop    ebx
.L442bf2:
 pop    ebp
.L442bf3:
 ret    0x8
.L442bf6:
 inc    DWORD PTR [esi+0x20]
.L442bf9:
 mov    DWORD PTR [esi+0x28],ebx
.L442bfc:
 mov    eax,DWORD PTR [esi+0x8]
.L442bff:
 cmp    eax,DWORD PTR [esi+0xc]
.L442c02:
 jne .L442ca0
.L442c08:
 cmp    DWORD PTR [esi+0x20],0x1
.L442c0c:
 je .L442c25
.L442c0e:
 push   ecx
.L442c0f:
 call   DWORD PTR [0x92d4b4]
.L442c15:
 inc    DWORD PTR [esi+0x24]
.L442c18:
 add    esp,0x4
.L442c1b:
 dec    DWORD PTR [esi+0x20]
.L442c1e:
 pop    edi
.L442c1f:
 pop    esi
.L442c20:
 pop    ebx
.L442c21:
 pop    ebp
.L442c22:
 ret    0x8
.L442c25:
 mov    eax,DWORD PTR [esi]
.L442c27:
 imul   eax,ebx
.L442c2a:
 push   eax
.L442c2b:
 call target_8f87c8
.L442c30:
 add    esp,0x4
.L442c33:
 mov    DWORD PTR [ebp+0xc],eax
.L442c36:
 lea    eax,[ebp+0xc]
.L442c39:
 lea    ecx,[esi+0x14]
.L442c3c:
 push   eax
.L442c3d:
 call target_42c2a0
.L442c42:
 mov    ecx,DWORD PTR [esi+0xc]
.L442c45:
 sub    ecx,DWORD PTR [esi+0x8]
.L442c48:
 mov    eax,DWORD PTR [esi+0x10]
.L442c4b:
 sub    eax,DWORD PTR [esi+0x8]
.L442c4e:
 sar    ecx,0x2
.L442c51:
 add    ecx,DWORD PTR [esi]
.L442c53:
 sar    eax,0x2
.L442c56:
 {load} cmp    eax,ecx
.L442c58:
 jae .L442c76
.L442c5a:
 cmp    ecx,0x3fffffff
.L442c60:
 jbe .L442c6d
.L442c62:
 push   0x999938
.L442c67:
 call   DWORD PTR [0x92d168]
.L442c6d:
 push   ecx
.L442c6e:
 lea    ecx,[esi+0x8]
.L442c71:
 call target_426800
.L442c76:
 mov    eax,DWORD PTR [esi]
.L442c78:
 dec    eax
.L442c79:
 imul   eax,ebx
.L442c7c:
 add    eax,DWORD PTR [ebp+0xc]
.L442c7f:
 mov    DWORD PTR [ebp+0x8],eax
.L442c82:
 cmp    eax,DWORD PTR [ebp+0xc]
.L442c85:
 jb .L442ca0
.L442c87:
 lea    eax,[ebp+0x8]
.L442c8a:
 push   eax
.L442c8b:
 lea    ecx,[esi+0x8]
.L442c8e:
 call target_42c2a0
.L442c93:
 mov    eax,DWORD PTR [ebp+0x8]
.L442c96:
 {load} sub    eax,ebx
.L442c98:
 mov    DWORD PTR [ebp+0x8],eax
.L442c9b:
 cmp    eax,DWORD PTR [ebp+0xc]
.L442c9e:
 jae .L442c87
.L442ca0:
 mov    eax,DWORD PTR [esi+0xc]
.L442ca3:
 pop    edi
.L442ca4:
 mov    eax,DWORD PTR [eax-0x4]
.L442ca7:
 add    DWORD PTR [esi+0xc],0xfffffffc
.L442cab:
 pop    esi
.L442cac:
 pop    ebx
.L442cad:
 pop    ebp
.L442cae:
 ret    0x8
.equ target_426800,0x426800
.equ target_42c2a0,0x42c2a0
.equ target_8f87c8,0x8f87c8
