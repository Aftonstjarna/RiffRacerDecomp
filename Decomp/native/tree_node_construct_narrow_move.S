.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA [0x423290,0x4232c4); following INT3 padding excluded.
.global original_tree_node_construct_narrow_move
.equ allocate_links,0x423560
.equ narrow_move_construct,0x416af0
original_tree_node_construct_narrow_move:
 push ebp
 mov.s ebp,esp
 push esi
 push edi
 call allocate_links
 mov.s esi,eax
 lea edi,[esi+0x10]
 mov WORD PTR [esi+0xc],0
 test edi,edi
 je .Ldone
 mov ecx,DWORD PTR [ebp+0xc]
 push DWORD PTR [ecx]
 mov.s ecx,edi
 call narrow_move_construct
 mov DWORD PTR [edi+0x18],0
 mov.s eax,esi
.Ldone:
 pop edi
 pop esi
 pop ebp
 ret 0xc
.section .note.GNU-stack,"",@progbits
