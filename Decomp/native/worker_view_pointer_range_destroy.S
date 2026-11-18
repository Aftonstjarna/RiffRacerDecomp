.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x43ee20.
.global original_worker_view_pointer_range_destroy
original_worker_view_pointer_range_destroy:
 push ebp
 {load} mov ebp,esp
 push esi
 mov esi,DWORD PTR [ebp+8]
 push edi
 mov edi,DWORD PTR [ebp+12]
 {load} cmp esi,edi
 je .Ldone
 nop
.Lloop:
 mov edx,DWORD PTR [esi]
 test edx,edx
 je .Lnext
 mov eax,DWORD PTR [edx]
 mov ecx,DWORD PTR [eax+4]
 {load} add ecx,edx
 dec DWORD PTR [ecx+4]
 jne .Lnext
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
.Lnext:
 add esi,4
 {load} cmp esi,edi
 jne .Lloop
.Ldone:
 pop edi
 pop esi
 pop ebp
 ret 8
.section .note.GNU-stack,"",@progbits
