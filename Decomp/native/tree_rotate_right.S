.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x4231e0 through 0x423238 exclusive. Right rotation, all three exits.
.global original_tree_rotate_right
original_tree_rotate_right:
 push ebp
 {load} mov ebp, esp
 mov edx, DWORD PTR [ebp+8]
 push esi
 mov esi, DWORD PTR [edx]
 mov eax, DWORD PTR [esi+8]
 mov DWORD PTR [edx], eax
 mov eax, DWORD PTR [esi+8]
 cmp BYTE PTR [eax+13], 0
 jne child_is_sentinel
 mov DWORD PTR [eax+4], edx
child_is_sentinel:
 mov eax, DWORD PTR [edx+4]
 mov DWORD PTR [esi+4], eax
 mov eax, DWORD PTR [ecx]
 cmp edx, DWORD PTR [eax+4]
 jne nonroot
 mov DWORD PTR [eax+4], esi
 mov DWORD PTR [esi+8], edx
 mov DWORD PTR [edx+4], esi
 pop esi
 pop ebp
 ret 4
nonroot:
 mov eax, DWORD PTR [edx+4]
 cmp edx, DWORD PTR [eax+8]
 jne left_child
 mov DWORD PTR [eax+8], esi
 mov DWORD PTR [esi+8], edx
 mov DWORD PTR [edx+4], esi
 pop esi
 pop ebp
 ret 4
left_child:
 mov DWORD PTR [eax], esi
 mov DWORD PTR [esi+8], edx
 mov DWORD PTR [edx+4], esi
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
