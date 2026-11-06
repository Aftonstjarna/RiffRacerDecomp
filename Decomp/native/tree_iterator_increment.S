# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x422e20,0x422e6f): tree iterator successor.
.intel_syntax noprefix
.code32
.text
.global original_tree_iterator_increment
original_tree_iterator_increment:
 mov.s edx,ecx
 mov eax,DWORD PTR [edx]
 cmp BYTE PTR [eax+0xd],0
 jne .Ldone
 mov ecx,DWORD PTR [eax+8]
 cmp BYTE PTR [ecx+0xd],0
 jne .Lparents
 mov eax,DWORD PTR [ecx]
 cmp BYTE PTR [eax+0xd],0
 jne .Lstore_child
 jmp .Lleft
 {disp8} lea ecx,[ecx+0]
.Lleft:
 mov.s ecx,eax
 mov eax,DWORD PTR [ecx]
 cmp BYTE PTR [eax+0xd],0
 je .Lleft
.Lstore_child:
 mov DWORD PTR [edx],ecx
 mov.s eax,edx
 ret
.Lparents:
 mov eax,DWORD PTR [eax+4]
 cmp BYTE PTR [eax+0xd],0
 jne .Lstore_parent
.Lclimb:
 mov ecx,DWORD PTR [edx]
 cmp ecx,DWORD PTR [eax+8]
 jne .Lstore_parent
 mov DWORD PTR [edx],eax
 mov eax,DWORD PTR [eax+4]
 cmp BYTE PTR [eax+0xd],0
 je .Lclimb
.Lstore_parent:
 mov DWORD PTR [edx],eax
.Ldone:
 mov.s eax,edx
 ret
.section .note.GNU-stack,"",@progbits
