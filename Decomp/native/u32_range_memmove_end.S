# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x43e770,0x43e79b). One straight-line path, one RET 12.
# Stack arguments: source begin, source end, destination. EAX = destination end.
.intel_syntax noprefix
.code32
.text
.global original_u32_range_memmove_end
.equ MEMMOVE_IAT,0x92d4a4
original_u32_range_memmove_end:
 push ebp
 mov.s ebp,esp
 mov ecx,DWORD PTR [ebp+8]
 mov eax,DWORD PTR [ebp+12]
 sub.s eax,ecx
 sar eax,2
 push esi
 lea esi,[eax*4+0]
 push esi
 push ecx
 push DWORD PTR [ebp+16]
 call DWORD PTR [MEMMOVE_IAT]
 add esp,12
 add.s eax,esi
 pop esi
 pop ebp
 ret 12
.section .note.GNU-stack,"",@progbits
