# Provenance: supported Game.exe SHA256
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump and private Ghidra export 00536250 (205 bytes).
# ECX=mutable destination; second of four stack slots=source string. First,
# third and fourth slots are unused; original ret 16 must be retained. Preserve
# EBX/ESI/EDI/EBP; return destination in EAX. Length/capacity fields are +10/+14,
# capacity >=8 selects heap WCHAR storage. Shift old characters right, then
# copy prefix; self-alias uses overlapping move rather than distinct copy.
# Empty source or false grow result returns unchanged; successful path updates
# length/terminator via 0044fab0. Overflow calls imported std::_Xlength_error
# with original external NUL-terminated "string too long" at 0099994c (checked).
# No local SEH or embedded data; allocation/length exceptions propagate.
# Unreconstructed grow, set-length, WCHAR copy/move helpers and IAT/error text
# remain address dependencies; no external bytes are credited by this span.
.intel_syntax noprefix
.code32
.text
.global original_wide_prepend
original_wide_prepend:
.L536250:
 push   ebp
.L536251:
 {load} mov    ebp,esp
.L536253:
 push   ebx
.L536254:
 mov    ebx,DWORD PTR [ebp+0xc]
.L536257:
 push   esi
.L536258:
 push   edi
.L536259:
 or     edi,0xffffffff
.L53625c:
 {load} mov    esi,ecx
.L53625e:
 cmp    DWORD PTR [ebx+0x10],0xffffffff
.L536262:
 cmovb  edi,DWORD PTR [ebx+0x10]
.L536266:
 or     eax,0xffffffff
.L536269:
 mov    ecx,DWORD PTR [esi+0x10]
.L53626c:
 {load} sub    eax,ecx
.L53626e:
 {load} cmp    eax,edi
.L536270:
 ja .L53627d
.L536272:
 push   offset string_too_long
.L536277:
 call   DWORD PTR [imported_length_error]
.L53627d:
 test   edi,edi
.L53627f:
 je .L536314
.L536285:
 lea    eax,[ecx+edi*1]
.L536288:
 {load} mov    ecx,esi
.L53628a:
 push   0x0
.L53628c:
 push   eax
.L53628d:
 mov    DWORD PTR [ebp+0xc],eax
.L536290:
 call wide_grow
.L536295:
 test   al,al
.L536297:
 je .L536314
.L536299:
 mov    eax,DWORD PTR [esi+0x14]
.L53629c:
 cmp    eax,0x8
.L53629f:
 jb .L5362a5
.L5362a1:
 mov    edx,DWORD PTR [esi]
.L5362a3:
 jmp .L5362a7
.L5362a5:
 {load} mov    edx,esi
.L5362a7:
 cmp    eax,0x8
.L5362aa:
 jb .L5362b0
.L5362ac:
 mov    eax,DWORD PTR [esi]
.L5362ae:
 jmp .L5362b2
.L5362b0:
 {load} mov    eax,esi
.L5362b2:
 push   DWORD PTR [esi+0x10]
.L5362b5:
 lea    ecx,[eax+edi*2]
.L5362b8:
 call wide_move
.L5362bd:
 add    esp,0x4
.L5362c0:
 {load} cmp    esi,ebx
.L5362c2:
 jne .L5362eb
.L5362c4:
 mov    eax,DWORD PTR [esi+0x14]
.L5362c7:
 cmp    eax,0x8
.L5362ca:
 jb .L5362d0
.L5362cc:
 mov    edx,DWORD PTR [esi]
.L5362ce:
 jmp .L5362d2
.L5362d0:
 {load} mov    edx,esi
.L5362d2:
 cmp    eax,0x8
.L5362d5:
 jb .L5362e1
.L5362d7:
 mov    ecx,DWORD PTR [esi]
.L5362d9:
 push   edi
.L5362da:
 call wide_move
.L5362df:
 jmp .L536307
.L5362e1:
 {load} mov    ecx,esi
.L5362e3:
 push   edi
.L5362e4:
 call wide_move
.L5362e9:
 jmp .L536307
.L5362eb:
 cmp    DWORD PTR [ebx+0x14],0x8
.L5362ef:
 jb .L5362f3
.L5362f1:
 mov    ebx,DWORD PTR [ebx]
.L5362f3:
 cmp    DWORD PTR [esi+0x14],0x8
.L5362f7:
 jb .L5362fd
.L5362f9:
 mov    ecx,DWORD PTR [esi]
.L5362fb:
 jmp .L5362ff
.L5362fd:
 {load} mov    ecx,esi
.L5362ff:
 push   edi
.L536300:
 {load} mov    edx,ebx
.L536302:
 call wide_copy
.L536307:
 add    esp,0x4
.L53630a:
 {load} mov    ecx,esi
.L53630c:
 push   DWORD PTR [ebp+0xc]
.L53630f:
 call wide_set_length
.L536314:
 pop    edi
.L536315:
 {load} mov    eax,esi
.L536317:
 pop    esi
.L536318:
 pop    ebx
.L536319:
 pop    ebp
.L53631a:
 ret    0x10
.equ wide_copy,0x44e120
.equ wide_move,0x44e140
.equ wide_set_length,0x44fab0
.equ wide_grow,0x44fc30

.equ imported_length_error,0x92d168
.equ string_too_long,0x99994c
