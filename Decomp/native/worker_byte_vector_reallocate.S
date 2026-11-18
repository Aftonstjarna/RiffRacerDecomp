# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x51a450.
.intel_syntax noprefix
.code32
.text
.global original_worker_byte_vector_reallocate
.equ allocate_iat,0x92d4b4
.equ allocation_failure_iat,0x92d164
.equ memmove_iat,0x92d4a4
.equ delete_iat,0x92d4b0
original_worker_byte_vector_reallocate:
 push ebp
 mov.s ebp,esp
 push ebx
 push esi
 push edi
 mov edi,[ebp+8]
 xor.s esi,esi
 mov.s ebx,ecx
 test edi,edi
 je .allocated
 cmp edi,-1
 ja .failure
 push edi
 call DWORD PTR [allocate_iat]
 mov.s esi,eax
 add esp,4
 test esi,esi
 jne .allocated
.failure:
 call DWORD PTR [allocation_failure_iat]
.allocated:
 mov ecx,[ebx]
 mov eax,[ebx+4]
 sub.s eax,ecx
 push eax
 push ecx
 push esi
 call DWORD PTR [memmove_iat]
 mov eax,[ebx]
 add esp,12
 mov ecx,[ebx+4]
 sub.s ecx,eax
 mov [ebp+8],ecx
 test eax,eax
 je .update
 push eax
 call DWORD PTR [delete_iat]
 mov ecx,[ebp+8]
 add esp,4
.update:
 lea eax,[esi+edi]
 mov [ebx],esi
 mov [ebx+8],eax
 lea eax,[esi+ecx]
 pop edi
 pop esi
 mov [ebx+4],eax
 pop ebx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
