.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x5614e0.
.equ grow, 0x561b80
.equ wide_move, 0x44f6f0
.global original_wide_entry_vector_append
original_wide_entry_vector_append:
 push ebp
 {load} mov ebp, esp
 push esi
 {load} mov esi, ecx
 push edi
 mov edi, [ebp+8]
 mov ecx, [esi+4]
 {load} cmp edi, ecx
 jae external
 mov eax, [esi]
 {load} cmp eax, edi
 ja external
 {load} sub edi, eax
 mov eax, 0x92492493
 imul edi
 {load} add edx, edi
 sar edx, 4
 {load} mov edi, edx
 shr edi, 31
 {load} add edi, edx
 cmp ecx, [esi+8]
 jne internal_ready
 push ecx
 {load} mov ecx, esi
 call grow
internal_ready:
 mov eax, [esi]
 lea ecx, [edi*8+0]
 {load} sub ecx, edi
 lea edx, [eax+ecx*4]
 mov ecx, [esi+4]
 test ecx, ecx
 je finish
 mov eax, [edx]
 mov [ecx], eax
 lea eax, [edx+4]
 push eax
 add ecx, 4
 call wide_move
 add DWORD PTR [esi+4], 28
 pop edi
 pop esi
 pop ebp
 ret 4
external:
 cmp ecx, [esi+8]
 jne external_ready
 push ecx
 {load} mov ecx, esi
 call grow
external_ready:
 mov ecx, [esi+4]
 test ecx, ecx
 je finish
 mov eax, [edi]
 mov [ecx], eax
 lea eax, [edi+4]
 push eax
 add ecx, 4
 call wide_move
finish:
 add DWORD PTR [esi+4], 28
 pop edi
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
