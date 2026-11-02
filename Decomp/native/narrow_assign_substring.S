# Reviewed against pinned depot SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Evidence: /tmp/cloud-narrow-dependencies/{exports/00415fe0.txt,narrow_assign_substring.asm,error-data.txt}.
# thiscall ECX=destination; stack source, offset, count; EAX=this; ret 12.
# Preserves EBP/EBX/ESI/EDI. Clamp count to source length-offset. Self-assign
# truncates to offset+count, terminates, then erases prefix via 416660.
# Distinct objects grow via 416890 if needed, select inline/heap by capacity
# >=16, memcpy through 8f8d66, set length/NUL (including empty paths).
# Original nonreturning out-of-range and length-error IAT calls 92d16c/92d168
# reference 99995c/99994c. No local EH frame; retain original post-call bytes
# despite decompiler's invented returning-error values. Growth/erase helpers
# remain unresolved, as do external strings and allocator/import dependencies.
# No embedded data; final ret ends at 4160f7 before int3 alignment.
# Original VA range 0x415fe0..0x4160f7
.intel_syntax noprefix
.code32
.text
.global original_narrow_assign_substring
original_narrow_assign_substring:
.L415fe0:
 push   ebp
.L415fe1:
 {load} mov    ebp,esp
.L415fe3:
 push   ebx
.L415fe4:
 mov    ebx,DWORD PTR [ebp+0x8]
.L415fe7:
 push   esi
.L415fe8:
 push   edi
.L415fe9:
 {load} mov    esi,ecx
.L415feb:
 mov    ecx,DWORD PTR [ebp+0xc]
.L415fee:
 mov    edi,DWORD PTR [ebx+0x10]
.L415ff1:
 {load} cmp    edi,ecx
.L415ff3:
 jae .L416000
.L415ff5:
 push   0x99995c
.L415ffa:
 call   DWORD PTR [0x92d16c]
.L416000:
 {load} sub    edi,ecx
.L416002:
 cmp    DWORD PTR [ebp+0x10],edi
.L416005:
 cmovb  edi,DWORD PTR [ebp+0x10]
.L416009:
 {load} cmp    esi,ebx
.L41600b:
 jne .L41605b
.L41600d:
 lea    eax,[edi+ecx*1]
.L416010:
 cmp    DWORD PTR [esi+0x10],eax
.L416013:
 jae .L416020
.L416015:
 push   0x99995c
.L41601a:
 call   DWORD PTR [0x92d16c]
.L416020:
 cmp    DWORD PTR [esi+0x14],0x10
.L416024:
 mov    DWORD PTR [esi+0x10],eax
.L416027:
 jb .L416042
.L416029:
 mov    edx,DWORD PTR [esi]
.L41602b:
 push   ecx
.L41602c:
 push   0x0
.L41602e:
 {load} mov    ecx,esi
.L416030:
 mov    BYTE PTR [edx+eax*1],0x0
.L416034:
 call target_416660
.L416039:
 pop    edi
.L41603a:
 {load} mov    eax,esi
.L41603c:
 pop    esi
.L41603d:
 pop    ebx
.L41603e:
 pop    ebp
.L41603f:
 ret    0xc
.L416042:
 {load} mov    edx,esi
.L416044:
 push   ecx
.L416045:
 push   0x0
.L416047:
 {load} mov    ecx,esi
.L416049:
 mov    BYTE PTR [edx+eax*1],0x0
.L41604d:
 call target_416660
.L416052:
 pop    edi
.L416053:
 {load} mov    eax,esi
.L416055:
 pop    esi
.L416056:
 pop    ebx
.L416057:
 pop    ebp
.L416058:
 ret    0xc
.L41605b:
 cmp    edi,0xfffffffe
.L41605e:
 jbe .L41606b
.L416060:
 push   0x99994c
.L416065:
 call   DWORD PTR [0x92d168]
.L41606b:
 mov    eax,DWORD PTR [esi+0x14]
.L41606e:
 {load} cmp    eax,edi
.L416070:
 jae .L416096
.L416072:
 push   DWORD PTR [esi+0x10]
.L416075:
 {load} mov    ecx,esi
.L416077:
 push   edi
.L416078:
 call target_416890
.L41607d:
 mov    ecx,DWORD PTR [ebp+0xc]
.L416080:
 test   edi,edi
.L416082:
 je .L4160ee
.L416084:
 cmp    DWORD PTR [ebx+0x14],0x10
.L416088:
 jb .L41608c
.L41608a:
 mov    ebx,DWORD PTR [ebx]
.L41608c:
 cmp    DWORD PTR [esi+0x14],0x10
.L416090:
 jb .L4160bc
.L416092:
 mov    edx,DWORD PTR [esi]
.L416094:
 jmp .L4160be
.L416096:
 test   edi,edi
.L416098:
 jne .L416084
.L41609a:
 mov    DWORD PTR [esi+0x10],edi
.L41609d:
 cmp    eax,0x10
.L4160a0:
 jb .L4160b0
.L4160a2:
 mov    eax,DWORD PTR [esi]
.L4160a4:
 pop    edi
.L4160a5:
 mov    BYTE PTR [eax],0x0
.L4160a8:
 {load} mov    eax,esi
.L4160aa:
 pop    esi
.L4160ab:
 pop    ebx
.L4160ac:
 pop    ebp
.L4160ad:
 ret    0xc
.L4160b0:
 {load} mov    eax,esi
.L4160b2:
 pop    edi
.L4160b3:
 pop    esi
.L4160b4:
 pop    ebx
.L4160b5:
 mov    BYTE PTR [eax],0x0
.L4160b8:
 pop    ebp
.L4160b9:
 ret    0xc
.L4160bc:
 {load} mov    edx,esi
.L4160be:
 test   edi,edi
.L4160c0:
 je .L4160d0
.L4160c2:
 push   edi
.L4160c3:
 lea    eax,[ebx+ecx*1]
.L4160c6:
 push   eax
.L4160c7:
 push   edx
.L4160c8:
 call target_8f8d66
.L4160cd:
 add    esp,0xc
.L4160d0:
 cmp    DWORD PTR [esi+0x14],0x10
.L4160d4:
 mov    DWORD PTR [esi+0x10],edi
.L4160d7:
 jb .L4160e8
.L4160d9:
 mov    eax,DWORD PTR [esi]
.L4160db:
 mov    BYTE PTR [eax+edi*1],0x0
.L4160df:
 {load} mov    eax,esi
.L4160e1:
 pop    edi
.L4160e2:
 pop    esi
.L4160e3:
 pop    ebx
.L4160e4:
 pop    ebp
.L4160e5:
 ret    0xc
.L4160e8:
 {load} mov    eax,esi
.L4160ea:
 mov    BYTE PTR [eax+edi*1],0x0
.L4160ee:
 pop    edi
.L4160ef:
 {load} mov    eax,esi
.L4160f1:
 pop    esi
.L4160f2:
 pop    ebx
.L4160f3:
 pop    ebp
.L4160f4:
 ret    0xc
.equ target_416660,0x416660
.equ target_416890,0x416890
.equ target_8f8d66,0x8f8d66
