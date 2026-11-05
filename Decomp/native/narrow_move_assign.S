# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x440a20,0x440a5e); following INT3 padding excluded.
# ECX=destination; [entry ESP+4]=source; EAX=destination; RET 4.
.intel_syntax noprefix
.code32
.text
.global original_narrow_move_assign
original_narrow_move_assign:
 push ebp
 mov.s ebp,esp
 push esi
 mov.s esi,ecx
 cmp esi,DWORD PTR [ebp+8]
 je .Lreturn
 cmp DWORD PTR [esi+0x14],0x10
 jb .Ltransfer
 push DWORD PTR [esi]
 call DWORD PTR [delete_iat]
 add esp,4
.Ltransfer:
 push DWORD PTR [ebp+8]
 mov DWORD PTR [esi+0x14],0xf
 mov.s ecx,esi
 mov DWORD PTR [esi+0x10],0
 mov BYTE PTR [esi],0
 call move_storage
.Lreturn:
 mov.s eax,esi
 pop esi
 pop ebp
 ret 4
.equ delete_iat,0x92d4b0
.equ move_storage,0x416fa0
.section .note.GNU-stack,"",@progbits
