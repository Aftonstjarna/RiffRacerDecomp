# Reviewed against supported Game.exe SHA256
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Ghidra ExportRecovery on private /tmp/cloud-append-batch database; bodies
# agree with original objdump instructions. No inline data or SEH frame.
# ECX=this; EAX returns this; EBP/EBX/ESI/EDI preserved when used.
# Wide string: length +0x10, capacity +0x14; capacity <8 selects inline data.
# External grow/set-length helpers remain address dependencies, not recovered here.
# VA [0x5360b0,0x536151), Ghidra inclusive end 0x536150; excludes INT3 padding.
# Three stack arguments: source string, position, count; callee pops 12 bytes.
# Checks position, clamps count to remaining source, checks length overflow,
# grows, copies count*2 bytes and updates length/terminator through 0x44fab0.
# Reloads source storage after grow, including self-append; memcpy is original.
# IAT 0x92d16c throws out_of_range using 0x99995c (invalid string position);
# IAT 0x92d168 throws length_error using 0x99994c (string too long).
# Both are nonreturning exception exits; no local cleanup/unwind handler.
.intel_syntax noprefix
.code32
.text
.global original_wide_append_substring
original_wide_append_substring:
.L5360b0:
 push   ebp
.L5360b1:
 {load} mov    ebp,esp
.L5360b3:
 push   ebx
.L5360b4:
 push   esi
.L5360b5:
 push   edi
.L5360b6:
 mov    edi,DWORD PTR [ebp+0x8]
.L5360b9:
 {load} mov    esi,ecx
.L5360bb:
 mov    ecx,DWORD PTR [ebp+0xc]
.L5360be:
 mov    eax,DWORD PTR [edi+0x10]
.L5360c1:
 {load} cmp    eax,ecx
.L5360c3:
 jae .L5360d0
.L5360c5:
 push   0x99995c
.L5360ca:
 call   DWORD PTR [0x92d16c]
.L5360d0:
 mov    ebx,DWORD PTR [ebp+0x10]
.L5360d3:
 {load} sub    eax,ecx
.L5360d5:
 mov    ecx,DWORD PTR [esi+0x10]
.L5360d8:
 {load} cmp    eax,ebx
.L5360da:
 mov    DWORD PTR [ebp+0x8],ecx
.L5360dd:
 cmovb  ebx,eax
.L5360e0:
 or     eax,0xffffffff
.L5360e3:
 {load} sub    eax,ecx
.L5360e5:
 {load} cmp    eax,ebx
.L5360e7:
 ja .L5360f4
.L5360e9:
 push   0x99994c
.L5360ee:
 call   DWORD PTR [0x92d168]
.L5360f4:
 test   ebx,ebx
.L5360f6:
 je .L536148
.L5360f8:
 lea    eax,[ecx+ebx*1]
.L5360fb:
 {load} mov    ecx,esi
.L5360fd:
 push   0x0
.L5360ff:
 push   eax
.L536100:
 call original_wide_grow
.L536105:
 test   al,al
.L536107:
 je .L536148
.L536109:
 cmp    DWORD PTR [edi+0x14],0x8
.L53610d:
 jb .L536111
.L53610f:
 mov    edi,DWORD PTR [edi]
.L536111:
 cmp    DWORD PTR [esi+0x14],0x8
.L536115:
 jb .L53611b
.L536117:
 mov    ecx,DWORD PTR [esi]
.L536119:
 jmp .L53611d
.L53611b:
 {load} mov    ecx,esi
.L53611d:
 test   ebx,ebx
.L53611f:
 je .L53613b
.L536121:
 lea    eax,[ebx+ebx*1]
.L536124:
 push   eax
.L536125:
 mov    eax,DWORD PTR [ebp+0xc]
.L536128:
 lea    eax,[edi+eax*2]
.L53612b:
 push   eax
.L53612c:
 mov    eax,DWORD PTR [esi+0x10]
.L53612f:
 lea    eax,[ecx+eax*2]
.L536132:
 push   eax
.L536133:
 call original_memcpy
.L536138:
 add    esp,0xc
.L53613b:
 mov    eax,DWORD PTR [ebp+0x8]
.L53613e:
 {load} mov    ecx,esi
.L536140:
 {load} add    eax,ebx
.L536142:
 push   eax
.L536143:
 call original_wide_set_length
.L536148:
 pop    edi
.L536149:
 {load} mov    eax,esi
.L53614b:
 pop    esi
.L53614c:
 pop    ebx
.L53614d:
 pop    ebp
.L53614e:
 ret    0xc
.equ original_wide_set_length,0x44fab0
.equ original_wide_grow,0x44fc30
.equ original_memcpy,0x8f8d66
