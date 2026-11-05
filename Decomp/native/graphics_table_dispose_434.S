# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4b2c60,0x4b2cb9); following seven INT3 bytes excluded.
# Shutdown caller: CALL at 0x4a0a0a. Both null branches join the final clear.
.intel_syntax noprefix
.code32
.text
.global original_graphics_table_dispose_434
original_graphics_table_dispose_434:
 push ebp
 mov.s ebp,esp
 # Preserve incoming ECX as the opaque trailing range-helper stack argument.
 push ecx
 push esi
 mov esi,DWORD PTR [table_global]
 test esi,esi
 je .Lclear_global
 mov ecx,DWORD PTR [esi]
 test ecx,ecx
 je .Ldelete_table
 push DWORD PTR [ebp-4]
 mov edx,DWORD PTR [esi+4]
 push ecx
 call range_destroy
 push DWORD PTR [esi]
 call DWORD PTR [operator_delete_iat]
 add esp,12
 mov DWORD PTR [esi],0
 mov DWORD PTR [esi+4],0
 mov DWORD PTR [esi+8],0
.Ldelete_table:
 push esi
 call DWORD PTR [operator_delete_iat]
 add esp,4
.Lclear_global:
 mov DWORD PTR [table_global],0
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
.equ table_global,0xc0d434
.equ range_destroy,0x49d990
.equ operator_delete_iat,0x92d4b0
.section .note.GNU-stack,"",@progbits
