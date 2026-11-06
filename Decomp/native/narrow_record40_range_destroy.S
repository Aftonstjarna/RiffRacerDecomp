# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x507f60,0x507fa2); INT3 padding excluded.
# Stack arguments: begin, end; callee pops 8. Stride 40 bytes.
.intel_syntax noprefix
.code32
.text
.equ scalar_delete_iat,0x92d4b0
.global original_narrow_record40_range_destroy
original_narrow_record40_range_destroy:
 push ebp
 mov.s ebp,esp
 push esi
 mov esi,DWORD PTR [ebp+8]
 push edi
 mov edi,DWORD PTR [ebp+12]
 cmp.s esi,edi
 je .Lreturn
 push ebx
 mov ebx,DWORD PTR [scalar_delete_iat]
.Lloop:
 cmp DWORD PTR [esi+20],16
 jb .Lreset
 push DWORD PTR [esi]
 call ebx
 add esp,4
.Lreset:
 mov DWORD PTR [esi+20],15
 mov DWORD PTR [esi+16],0
 mov BYTE PTR [esi],0
 add esi,40
 cmp.s esi,edi
 jne .Lloop
 pop ebx
.Lreturn:
 pop edi
 pop esi
 pop ebp
 ret 8
.section .note.GNU-stack,"",@progbits
