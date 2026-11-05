# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x416fa0,0x416ff5); following INT3 padding excluded.
# ECX=destination; stack argument=source; callee pops 4 bytes.
.intel_syntax noprefix
.code32
.text
.global original_narrow_move_storage
original_narrow_move_storage:
 push ebp
 mov.s ebp,esp
 push esi
 mov esi,DWORD PTR [ebp+8]
 push edi
 mov.s edi,ecx
 cmp DWORD PTR [esi+20],16
 jae .Lheap
 mov eax,DWORD PTR [esi+16]
 inc eax
 je .Lmetadata
 push eax
 push esi
 push edi
 call DWORD PTR [memmove_iat]
 add esp,12
 jmp .Lmetadata
.Lheap:
 test edi,edi
 je .Lclear_pointer
 mov eax,DWORD PTR [esi]
 mov DWORD PTR [edi],eax
.Lclear_pointer:
 mov DWORD PTR [esi],0
.Lmetadata:
 mov eax,DWORD PTR [esi+16]
 mov DWORD PTR [edi+16],eax
 mov eax,DWORD PTR [esi+20]
 mov DWORD PTR [edi+20],eax
 mov DWORD PTR [esi+20],15
 mov DWORD PTR [esi+16],0
 pop edi
 mov BYTE PTR [esi],0
 pop esi
 pop ebp
 ret 4
.equ memmove_iat,0x92d4a4
.section .note.GNU-stack,"",@progbits
