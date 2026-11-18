.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x5c20e0.
.equ grow,0x519d50
.global original_worker_byte_vector_append
original_worker_byte_vector_append:
 push ebp
 {load} mov ebp,esp
 push esi
 {load} mov esi,ecx
 push edi
 mov edi,DWORD PTR [ebp+8]
 mov eax,DWORD PTR [esi+4]
 {load} cmp edi,eax
 jae external_source
 mov ecx,DWORD PTR [esi]
 {load} cmp ecx,edi
 ja external_source
 {load} sub edi,ecx
 cmp eax,DWORD PTR [esi+8]
 jne internal_ready
 push 1
 {load} mov ecx,esi
 call grow
internal_ready:
 mov ecx,DWORD PTR [esi+4]
 test ecx,ecx
 je advance
 mov eax,DWORD PTR [esi]
 mov al,BYTE PTR [edi+eax]
 mov BYTE PTR [ecx],al
 inc DWORD PTR [esi+4]
 pop edi
 pop esi
 pop ebp
 ret 4
external_source:
 cmp eax,DWORD PTR [esi+8]
 jne external_ready
 push 1
 {load} mov ecx,esi
 call grow
external_ready:
 mov ecx,DWORD PTR [esi+4]
 test ecx,ecx
 je advance
 mov al,BYTE PTR [edi]
 mov BYTE PTR [ecx],al
advance:
 inc DWORD PTR [esi+4]
 pop edi
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
