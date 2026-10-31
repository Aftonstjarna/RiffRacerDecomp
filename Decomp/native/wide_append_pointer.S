# Reviewed against supported Game.exe SHA256
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Ghidra ExportRecovery on private /tmp/cloud-append-batch database; bodies
# agree with original objdump instructions. No inline data or SEH frame.
# ECX=this; EAX returns this; EBP/EBX/ESI/EDI preserved when used.
# Wide string: length +0x10, capacity +0x14; capacity <8 selects inline data.
# External grow/set-length helpers remain address dependencies, not recovered here.
# VA [0x536160,0x536220), Ghidra inclusive end 0x53621f; next routine at 0x536220.
# Two stack arguments: UTF-16 pointer and count; both returns pop 8 bytes.
# A nonnull pointer inside [data,data+length*2) routes through substring append
# with this as source and a character offset, preserving aliasing across growth.
# Other pointers use overflow check, grow, memcpy(count*2), then set length.
# Null pointer is not rejected: zero count skips copying, exactly as original.
# Length overflow calls nonreturning IAT 0x92d168 with 0x99994c (string too long).
# No local exception cleanup; no embedded tables, literals or alignment padding.
.intel_syntax noprefix
.code32
.text
.global original_wide_append_pointer
original_wide_append_pointer:
.L536160:
 push   ebp
.L536161:
 {load} mov    ebp,esp
.L536163:
 push   esi
.L536164:
 push   edi
.L536165:
 mov    edi,DWORD PTR [ebp+0x8]
.L536168:
 {load} mov    esi,ecx
.L53616a:
 test   edi,edi
.L53616c:
 je .L5361b6
.L53616e:
 mov    ecx,DWORD PTR [esi+0x14]
.L536171:
 cmp    ecx,0x8
.L536174:
 jb .L53617a
.L536176:
 mov    eax,DWORD PTR [esi]
.L536178:
 jmp .L53617c
.L53617a:
 {load} mov    eax,esi
.L53617c:
 {load} cmp    edi,eax
.L53617e:
 jb .L5361b6
.L536180:
 cmp    ecx,0x8
.L536183:
 jb .L536189
.L536185:
 mov    edx,DWORD PTR [esi]
.L536187:
 jmp .L53618b
.L536189:
 {load} mov    edx,esi
.L53618b:
 mov    eax,DWORD PTR [esi+0x10]
.L53618e:
 lea    eax,[edx+eax*2]
.L536191:
 {load} cmp    eax,edi
.L536193:
 jbe .L5361b6
.L536195:
 cmp    ecx,0x8
.L536198:
 jb .L53619e
.L53619a:
 mov    eax,DWORD PTR [esi]
.L53619c:
 jmp .L5361a0
.L53619e:
 {load} mov    eax,esi
.L5361a0:
 push   DWORD PTR [ebp+0xc]
.L5361a3:
 {load} sub    edi,eax
.L5361a5:
 {load} mov    ecx,esi
.L5361a7:
 sar    edi,1
.L5361a9:
 push   edi
.L5361aa:
 push   esi
.L5361ab:
 call original_wide_append_substring_address
.L5361b0:
 pop    edi
.L5361b1:
 pop    esi
.L5361b2:
 pop    ebp
.L5361b3:
 ret    0x8
.L5361b6:
 mov    ecx,DWORD PTR [esi+0x10]
.L5361b9:
 or     eax,0xffffffff
.L5361bc:
 push   ebx
.L5361bd:
 mov    ebx,DWORD PTR [ebp+0xc]
.L5361c0:
 {load} sub    eax,ecx
.L5361c2:
 {load} cmp    eax,ebx
.L5361c4:
 ja .L5361d1
.L5361c6:
 push   0x99994c
.L5361cb:
 call   DWORD PTR [0x92d168]
.L5361d1:
 test   ebx,ebx
.L5361d3:
 je .L536217
.L5361d5:
 lea    eax,[ecx+ebx*1]
.L5361d8:
 {load} mov    ecx,esi
.L5361da:
 push   0x0
.L5361dc:
 push   eax
.L5361dd:
 mov    DWORD PTR [ebp+0xc],eax
.L5361e0:
 call original_wide_grow
.L5361e5:
 test   al,al
.L5361e7:
 je .L536217
.L5361e9:
 cmp    DWORD PTR [esi+0x14],0x8
.L5361ed:
 jb .L5361f3
.L5361ef:
 mov    ecx,DWORD PTR [esi]
.L5361f1:
 jmp .L5361f5
.L5361f3:
 {load} mov    ecx,esi
.L5361f5:
 test   ebx,ebx
.L5361f7:
 je .L53620d
.L5361f9:
 lea    eax,[ebx+ebx*1]
.L5361fc:
 push   eax
.L5361fd:
 mov    eax,DWORD PTR [esi+0x10]
.L536200:
 push   edi
.L536201:
 lea    eax,[ecx+eax*2]
.L536204:
 push   eax
.L536205:
 call original_memcpy
.L53620a:
 add    esp,0xc
.L53620d:
 push   DWORD PTR [ebp+0xc]
.L536210:
 {load} mov    ecx,esi
.L536212:
 call original_wide_set_length
.L536217:
 pop    ebx
.L536218:
 pop    edi
.L536219:
 {load} mov    eax,esi
.L53621b:
 pop    esi
.L53621c:
 pop    ebp
.L53621d:
 ret    0x8
.equ original_wide_set_length,0x44fab0
.equ original_wide_grow,0x44fc30
.equ original_wide_append_substring_address,0x5360b0
.equ original_memcpy,0x8f8d66
