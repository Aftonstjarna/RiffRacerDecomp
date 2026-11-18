.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x440cc0.
.global original_worker_quad_vector_reserve
original_worker_quad_vector_reserve:
 push ebp
 {load} mov ebp,esp
 push esi
 mov esi,DWORD PTR [ebp+0x8]
 push edi
 {load} mov edi,ecx
 mov eax,DWORD PTR [edi+0x8]
 {load} sub eax,DWORD PTR [edi]
 sar eax,1
 {load} cmp eax,esi
 jae .Lsecond
 cmp esi,0x7fffffff
 jbe .Lgrow1
 push 0x999938
 call DWORD PTR [0x92d168]
.Lgrow1:
 push esi
 call target_41c560
.Lsecond:
 mov eax,DWORD PTR [edi+0x20]
 lea ecx,[edi+0x18]
 {load} sub eax,DWORD PTR [ecx]
 sar eax,1
 {load} cmp eax,esi
 jae .Lthird
 cmp esi,0x7fffffff
 jbe .Lgrow2
 push 0x999938
 call DWORD PTR [0x92d168]
.Lgrow2:
 push esi
 call target_41c560
.Lthird:
 mov eax,DWORD PTR [edi+0x14]
 lea ecx,[edi+0xc]
 {load} sub eax,DWORD PTR [ecx]
 sar eax,1
 {load} cmp eax,esi
 jae .Lfourth
 cmp esi,0x7fffffff
 jbe .Lgrow3
 push 0x999938
 call DWORD PTR [0x92d168]
.Lgrow3:
 push esi
 call target_41c560
.Lfourth:
 mov eax,DWORD PTR [edi+0x2c]
 lea ecx,[edi+0x24]
 {load} sub eax,DWORD PTR [ecx]
 sar eax,3
 {load} cmp eax,esi
 jae .Ldone
 cmp esi,0x1fffffff
 jbe .Lgrow4
 push 0x999938
 call DWORD PTR [0x92d168]
.Lgrow4:
 push esi
 call target_41c5e0
.Ldone:
 pop edi
 pop esi
 pop ebp
 ret 0x4
.equ target_41c560,0x41c560
.equ target_41c5e0,0x41c5e0
.section .note.GNU-stack,"",@progbits
