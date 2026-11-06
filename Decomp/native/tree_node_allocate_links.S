# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x423560,0x423598). No payload or flag initialization here.
.intel_syntax noprefix
.code32
.text
.global original_tree_node_allocate_links
original_tree_node_allocate_links:
 push esi
 push 0x2c
 mov.s esi,ecx
 call DWORD PTR [allocate_iat]
 mov.s edx,eax
 add esp,4
 test edx,edx
 jne .Llinks
 call DWORD PTR [bad_alloc_iat]
.Llinks:
 mov eax,DWORD PTR [esi]
 lea ecx,[edx+4]
 mov DWORD PTR [edx],eax
 test ecx,ecx
 je .Lright
 mov eax,DWORD PTR [esi]
 mov DWORD PTR [ecx],eax
.Lright:
 lea ecx,[edx+8]
 test ecx,ecx
 je .Ldone
 mov eax,DWORD PTR [esi]
 mov DWORD PTR [ecx],eax
.Ldone:
 mov.s eax,edx
 pop esi
 ret
.equ allocate_iat,0x92d4b4
.equ bad_alloc_iat,0x92d164
.section .note.GNU-stack,"",@progbits
