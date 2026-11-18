# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x43f030.
.intel_syntax noprefix
.code32
.text
.global original_worker_ref_pointer_range_copy
original_worker_ref_pointer_range_copy:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+0x8]
 push esi
 push edi
 mov.s edi,edx
 mov.s esi,ecx
 cmp.s esi,edi
 je .Ldone
.Lloop:
 test.s eax,eax
 je .Lnext
 mov edx,DWORD PTR [esi]
 mov DWORD PTR [eax],edx
 test.s edx,edx
 je .Lnext
 mov ecx,DWORD PTR [edx]
 mov ecx,DWORD PTR [ecx+0x4]
 inc DWORD PTR [ecx+edx+0x4]
.Lnext:
 add esi,4
 add eax,4
 cmp.s esi,edi
 jne .Lloop
.Ldone:
 pop edi
 pop esi
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
