# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x519d50..0x519dbb.
.intel_syntax noprefix
.code32
.text
.global original_worker_byte_vector_ensure_spare
.equ reallocate,0x51a450
.equ length_error_iat,0x92d168
original_worker_byte_vector_ensure_spare:
 push ebp
 mov.s ebp,esp
 mov edx,[ecx+8]
 mov.s eax,edx
 push esi
 mov esi,[ecx+4]
 sub.s eax,esi
 push edi
 mov edi,[ebp+8]
 cmp.s eax,edi
 jae .done
 push ebx
 mov ebx,[ecx]
 mov.s eax,ebx
 sub.s eax,esi
 dec eax
 cmp.s eax,edi
 jae .capacity
 push 0x999938
 call DWORD PTR [length_error_iat]
.capacity:
 sub.s esi,ebx
 sub.s edx,ebx
 add.s esi,edi
 or eax,-1
 mov.s edi,edx
 shr edi,1
 sub.s eax,edi
 pop ebx
 cmp.s eax,edx
 jae .normal
 xor.s edx,edx
 cmp.s edx,esi
 pop edi
 cmovb edx,esi
 pop esi
 mov [ebp+8],edx
 pop ebp
 jmp reallocate
.normal:
 add.s edx,edi
 cmp.s edx,esi
 pop edi
 cmovb edx,esi
 pop esi
 mov [ebp+8],edx
 pop ebp
 jmp reallocate
.done:
 pop edi
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
