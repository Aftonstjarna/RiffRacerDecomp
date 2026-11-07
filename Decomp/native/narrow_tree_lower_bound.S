# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x422d40,0x422e19).
.intel_syntax noprefix
.code32
.text
.global original_narrow_tree_lower_bound
original_narrow_tree_lower_bound:
# ECX: tree object containing head pointer. [ESP+4]: narrow-string query.
# Node links: left +0, root/parent +4, right +8; sentinel +13; key +16.
# No external calls, globals, imports, or writes outside this stack frame.
 push   ebp
 {load} mov    ebp,esp
 sub    esp,0x8
 push   ebx
 mov    ebx,DWORD PTR [ecx]
 push   edi
 mov    DWORD PTR [ebp-0x8],ebx
 mov    edi,DWORD PTR [ebx+0x4]
 cmp    BYTE PTR [edi+0xd],0x0
 jne    .L422e0f
 mov    edx,DWORD PTR [ebp+0x8]
 push   esi
 mov    ecx,DWORD PTR [edx+0x10]
 mov    DWORD PTR [ebp-0x4],ecx
# Compare query and node key; capacity >= 16 selects heap storage.
.L422d64:
 cmp    DWORD PTR [edx+0x14],0x10
 lea    eax,[edi+0x10]
 jb     .L422d71
 mov    esi,DWORD PTR [edx]
 jmp    .L422d73
.L422d71:
 {load} mov    esi,edx
.L422d73:
 cmp    DWORD PTR [eax+0x14],0x10
 mov    ebx,DWORD PTR [eax+0x10]
 jb     .L422d7e
 mov    eax,DWORD PTR [eax]
.L422d7e:
 {load} cmp    ebx,ecx
 {load} mov    edx,ecx
 cmovb  edx,ebx
 test   edx,edx
 je     .L422de3
 sub    edx,0x4
 jb     .L422da1
 {load} mov    edi,edi
# Equal four-byte chunks advance; mismatches are ordered byte by byte.
.L422d90:
 mov    ecx,DWORD PTR [eax]
 cmp    ecx,DWORD PTR [esi]
 jne    .L422da6
 add    eax,0x4
 add    esi,0x4
 sub    edx,0x4
 jae    .L422d90
.L422da1:
 cmp    edx,0xfffffffc
 je     .L422dda
.L422da6:
 mov    cl,BYTE PTR [eax]
 cmp    cl,BYTE PTR [esi]
 jne    .L422dd3
 cmp    edx,0xfffffffd
 je     .L422dda
 mov    cl,BYTE PTR [eax+0x1]
 cmp    cl,BYTE PTR [esi+0x1]
 jne    .L422dd3
 cmp    edx,0xfffffffe
 je     .L422dda
 mov    cl,BYTE PTR [eax+0x2]
 cmp    cl,BYTE PTR [esi+0x2]
 jne    .L422dd3
 cmp    edx,0xffffffff
 je     .L422dda
 mov    al,BYTE PTR [eax+0x3]
 cmp    al,BYTE PTR [esi+0x3]
 je     .L422dda
.L422dd3:
 {load} sbb    eax,eax
 or     eax,0x1
 jmp    .L422ddc
.L422dda:
 {load} xor    eax,eax
.L422ddc:
 mov    ecx,DWORD PTR [ebp-0x4]
 test   eax,eax
 jne    .L422df0
# Equal prefixes are ordered by unsigned string length.
.L422de3:
 {load} cmp    ebx,ecx
 jb     .L422dfb
 {load} xor    eax,eax
 {load} cmp    ebx,ecx
 setne  al
 test   eax,eax
# Negative node-key comparison descends right; otherwise save candidate and descend left.
.L422df0:
 js     .L422dfb
 {load} mov    ebx,edi
 mov    edi,DWORD PTR [edi]
 mov    DWORD PTR [ebp-0x8],ebx
 jmp    .L422e01
.L422dfb:
 mov    edi,DWORD PTR [edi+0x8]
 mov    ebx,DWORD PTR [ebp-0x8]
# Sentinel byte +13 ends traversal.
.L422e01:
 cmp    BYTE PTR [edi+0xd],0x0
 mov    edx,DWORD PTR [ebp+0x8]
 je     .L422d64
 pop    esi
# Empty tree skips the ESI save/restore; return candidate or sentinel.
.L422e0f:
 pop    edi
 {load} mov    eax,ebx
 pop    ebx
 {load} mov    esp,ebp
 pop    ebp
 ret    0x4
.section .note.GNU-stack,"",@progbits
