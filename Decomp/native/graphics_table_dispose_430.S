# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x4b2c00..0x4b2c59 exclusive; int3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_graphics_table_dispose_430
original_graphics_table_dispose_430:
 push ebp
 {load} mov ebp,esp
 # Save incoming ECX as the opaque trailing range-helper stack tag.
 push ecx
 push esi
 mov esi,DWORD PTR [table_global]
 test esi,esi
 je .Lclear_global
 mov ecx,DWORD PTR [esi]
 test ecx,ecx
 je .Ldelete_table
 push DWORD PTR [ebp-0x4]
 mov edx,DWORD PTR [esi+0x4]
 push ecx
 call range_destroy
 push DWORD PTR [esi]
 call DWORD PTR [operator_delete_iat]
 add esp,0xc
 mov DWORD PTR [esi],0x0
 mov DWORD PTR [esi+0x4],0x0
 mov DWORD PTR [esi+0x8],0x0
.Ldelete_table:
 push esi
 call DWORD PTR [operator_delete_iat]
 add esp,0x4
.Lclear_global:
 mov DWORD PTR [table_global],0x0
 pop esi
 {load} mov esp,ebp
 pop ebp
 ret
.equ table_global,0xc0d430
.equ range_destroy,0x49d820
.equ operator_delete_iat,0x92d4b0
.section .note.GNU-stack,"",@progbits
