.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x490eb0,0x490ef8); trailing INT3 padding excluded.
.global original_owner_slot214_assign
original_owner_slot214_assign:
 push ebp
 mov.s ebp,esp
 push esi
 mov esi,DWORD PTR [ebp+8]
 push edi
 mov.s edi,ecx
 mov edx,DWORD PTR [edi+0x214]
 cmp.s edx,esi
 je .Ldone
 test edx,edx
 je .Lstore
 mov eax,DWORD PTR [edx+4]
 lea ecx,[edx+4]
 mov eax,DWORD PTR [eax+4]
 add.s ecx,eax
 dec DWORD PTR [ecx+4]
 jne .Lstore
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
.Lstore:
 mov DWORD PTR [edi+0x214],esi
 test esi,esi
 je .Ldone
 mov eax,DWORD PTR [esi+4]
 mov eax,DWORD PTR [eax+4]
 inc DWORD PTR [eax+esi+8]
.Ldone:
 pop edi
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
