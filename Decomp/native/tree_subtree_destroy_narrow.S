.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x423110,0x423176). Recursive right subtree, iterative left subtree.
.global original_tree_subtree_destroy_narrow
original_tree_subtree_destroy_narrow:
 push ebp
 {load} mov ebp,esp
 push ecx
 push esi
 mov esi,DWORD PTR [ebp+8]
 {load} mov eax,ecx
 push edi
 mov DWORD PTR [ebp-4],eax
 {load} mov edi,esi
 cmp BYTE PTR [esi+13],0
 jne done
 push ebx
 mov ebx,DWORD PTR ds:0x92d4b0
 {disp8} lea ecx,[ecx+0]
loop_nodes:
 push DWORD PTR [edi+8]
 {load} mov ecx,eax
 call original_tree_subtree_destroy_narrow
 cmp DWORD PTR [esi+36],16
 mov edi,DWORD PTR [edi]
 jb inline_storage
 push DWORD PTR [esi+16]
 call ebx
 add esp,4
inline_storage:
 mov DWORD PTR [esi+36],15
 mov DWORD PTR [esi+32],0
 push esi
 mov BYTE PTR [esi+16],0
 call ebx
 mov eax,DWORD PTR [ebp-4]
 add esp,4
 cmp BYTE PTR [edi+13],0
 {load} mov esi,edi
 je loop_nodes
 pop ebx
done:
 pop edi
 pop esi
 {load} mov esp,ebp
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
