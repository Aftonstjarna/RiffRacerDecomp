# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x440a90..0x440ac7 exclusive; one straight-line return path.
# ECX=source string; stack destination, offset, count; returns destination.
# Initializes empty 24-byte narrow storage then delegates substring assignment.
.intel_syntax noprefix
.code32
.text
.global original_narrow_substring_construct
.equ assign_substring,0x415fe0
original_narrow_substring_construct:
 push ebp
 {load} mov ebp,esp
 push ecx
 push esi
 push DWORD PTR [ebp+0x10]
 mov esi,DWORD PTR [ebp+0x8]
 push DWORD PTR [ebp+0xc]
 mov DWORD PTR [ebp-4],0
 push ecx
 mov DWORD PTR [esi+0x14],0xf
 {load} mov ecx,esi
 mov DWORD PTR [esi+0x10],0
 mov BYTE PTR [esi],0
 call assign_substring
 {load} mov eax,esi
 pop esi
 {load} mov esp,ebp
 pop ebp
 ret 0xc
.section .note.GNU-stack,"",@progbits
