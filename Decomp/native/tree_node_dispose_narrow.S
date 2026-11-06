# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x423520,0x42355a). Node disposal with embedded narrow string.
.intel_syntax noprefix
.code32
.text
.global original_tree_node_dispose_narrow
.equ scalar_delete_iat,0x92d4b0
original_tree_node_dispose_narrow:
 push ebp
 mov.s ebp,esp
 push esi
 mov esi,DWORD PTR [ebp+8]
 cmp DWORD PTR [esi+0x24],0x10
 jb .Lreset
 push DWORD PTR [esi+0x10]
 call DWORD PTR [scalar_delete_iat]
 add esp,4
.Lreset:
 mov DWORD PTR [esi+0x24],0xf
 mov DWORD PTR [esi+0x20],0
 push esi
 mov BYTE PTR [esi+0x10],0
 call DWORD PTR [scalar_delete_iat]
 add esp,4
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
