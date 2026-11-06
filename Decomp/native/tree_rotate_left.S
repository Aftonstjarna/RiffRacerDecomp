.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x423180,0x4231d4); all three return paths included.
.global original_tree_rotate_left
original_tree_rotate_left:
 push ebp
 {load} mov ebp,esp
 mov edx,DWORD PTR [ebp+8]
 push esi
 mov esi,DWORD PTR [edx+8]
 mov eax,DWORD PTR [esi]
 mov DWORD PTR [edx+8],eax
 mov eax,DWORD PTR [esi]
 cmp BYTE PTR [eax+13],0
 jne child_is_nil
 mov DWORD PTR [eax+4],edx
child_is_nil:
 mov eax,DWORD PTR [edx+4]
 mov DWORD PTR [esi+4],eax
 mov eax,DWORD PTR [ecx]
 cmp edx,DWORD PTR [eax+4]
 jne nonroot
 mov DWORD PTR [eax+4],esi
 mov DWORD PTR [esi],edx
 mov DWORD PTR [edx+4],esi
 pop esi
 pop ebp
 ret 4
nonroot:
 mov eax,DWORD PTR [edx+4]
 cmp edx,DWORD PTR [eax]
 jne right_child
 mov DWORD PTR [eax],esi
 mov DWORD PTR [esi],edx
 mov DWORD PTR [edx+4],esi
 pop esi
 pop ebp
 ret 4
right_child:
 mov DWORD PTR [eax+8],esi
 mov DWORD PTR [esi],edx
 mov DWORD PTR [edx+4],esi
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
