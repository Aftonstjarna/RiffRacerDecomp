.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x416af0,0x416b54); following INT3 padding excluded.
.equ memmove_iat,0x92d4a4
.global original_narrow_move_construct
original_narrow_move_construct:
 push ebp
 {load} mov ebp,esp
 push esi
 mov esi,DWORD PTR [ebp+8]
 push edi
 {load} mov edi,ecx
 mov DWORD PTR [edi+0x14],15
 mov DWORD PTR [edi+0x10],0
 mov BYTE PTR [edi],0
 cmp DWORD PTR [esi+0x14],16
 jae heap_transfer
 mov eax,DWORD PTR [esi+0x10]
 inc eax
 je publish
 push eax
 push esi
 push edi
 call DWORD PTR [memmove_iat]
 add esp,12
 jmp publish
heap_transfer:
 mov eax,DWORD PTR [esi]
 mov DWORD PTR [edi],eax
 mov DWORD PTR [esi],0
publish:
 mov eax,DWORD PTR [esi+0x10]
 mov DWORD PTR [edi+0x10],eax
 mov eax,DWORD PTR [esi+0x14]
 mov DWORD PTR [edi+0x14],eax
 {load} mov eax,edi
 mov DWORD PTR [esi+0x14],15
 mov DWORD PTR [esi+0x10],0
 pop edi
 mov BYTE PTR [esi],0
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
